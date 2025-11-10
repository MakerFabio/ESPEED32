/*********************************************************************************************************************/
/*------------------------------------------------------Includes-----------------------------------------------------*/
/*********************************************************************************************************************/
#include "HAL.h"
#include "slot_ESC.h"
#include <math.h>

#ifdef AS5600_MAG
  #include "AS5600.h"
  AS5600 as5600;   // define magnnetic sensor, use default Wire

#elif defined (AS5600L_MAG)
  #include "AS5600L.h"
  AS5600L as5600;// define magnnetic sensor,use default Wire the 5600L has differnt address

#elif defined (MT6701_MAG)
  #include "MT6701.hpp"
  MT6701 mt6701; // magnetic sensor, install MT6701 library by Noran Raskin

#elif defined (TLE493D_P3B6_A0)
  #define ADDRESS 0x5D              // TLE493D-P3B6 A0 variant I2C address
  #define CONFIG_REG 0x0A           // Configuration register for P3B6 A0
  #include <Wire.h>

#elif defined (TLE493D_W2B6_A3)
  #define ADDRESS 0x44              // TLE493D-W2B6 A3 variant I2C address
  #define MOD1_REG 0x11             // MOD1 register address for A3 variant
  #define MOD1_CONFIG 0b11110111    // 7-byte read mode, fast mode, low power disabled
  #include <Wire.h>                 // default I2C library

#endif

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/

void HAL_InitHW()
{
  /* Setup fo the parameters for serial(debug) communication */ 
  Serial.begin(115200);   // debug restore me 

#if defined (TLE493D_P3B6_A0)
  Wire1.begin(SDA0_PIN, SCL0_PIN, 1000000L);
  Wire1.beginTransmission(ADDRESS);
  Wire1.write(CONFIG_REG);
  Wire1.write(0xC6);
  Wire1.write(0x02);
  Wire1.endTransmission();
#elif defined (TLE493D_W2B6_A3)
  Wire1.begin(SDA0_PIN, SCL0_PIN, 100000L); // DEbug added for secon I2C
  delay(100); // wait for I2C to stabilize
  
  Wire1.beginTransmission(ADDRESS); // Sensor address
  Wire1.write(MOD1_REG);             // Register address
  Wire1.write(MOD1_CONFIG);          // Configuration data
  Wire1.endTransmission();
#endif

  /* configure motor control PWM functionalitites and attach the channel to the GPIO to be controlled */
  ledcAttachChannel(HB_IN_PIN, PWM_FREQ_DEFAULT*1000, THR_PWM_RES_BIT, THR_IN_PWM_CHAN);
  ledcAttachChannel(HB_INH_PIN, PWM_FREQ_DEFAULT*1000, THR_PWM_RES_BIT, THR_INH_PWM_CHAN);

/* LEDC Chan to Group/Channel/Timer Mapping
** ledc: 0  => Group: 0, Channel: 0, Timer: 0
** ledc: 1  => Group: 0, Channel: 1, Timer: 0
** ledc: 2  => Group: 0, Channel: 2, Timer: 1
** ledc: 3  => Group: 0, Channel: 3, Timer: 1
** ledc: 4  => Group: 0, Channel: 4, Timer: 2
** ledc: 5  => Group: 0, Channel: 5, Timer: 2
** ledc: 6  => Group: 0, Channel: 6, Timer: 3
** ledc: 7  => Group: 0, Channel: 7, Timer: 3
** ledc: 8  => Group: 1, Channel: 0, Timer: 0
** ledc: 9  => Group: 1, Channel: 1, Timer: 0
** ledc: 10 => Group: 1, Channel: 2, Timer: 1
** ledc: 11 => Group: 1, Channel: 3, Timer: 1
** ledc: 12 => Group: 1, Channel: 4, Timer: 2
** ledc: 13 => Group: 1, Channel: 5, Timer: 2
** ledc: 14 => Group: 1, Channel: 6, Timer: 3
** ledc: 15 => Group: 1, Channel: 7, Timer: 3
*/
}

void HALanalogWrite (const int PWMchan, int value)
{
  /* Adapted to new 3.0.0 ESP32 library --> ledcWrite takes input PIN, not CHANNEL */
  switch (PWMchan)
  {
    case THR_IN_PWM_CHAN:
      ledcWrite(HB_IN_PIN, (uint32_t)value);
      break;

    case THR_INH_PWM_CHAN:
      ledcWrite(HB_INH_PIN, (uint32_t)value);
      break;
    
    default:
      break;
  }
}


int16_t HAL_ReadTriggerRaw()
{
  uint16_t retVal = 0;

  #if defined (AS5600_MAG) || defined (AS5600L)
    retVal = as5600.readAngle();

  #elif defined (MT6701_MAG)
    retVal = mt6701.getAngleDegrees();

  #elif defined (ANALOG_TRIG)
    retVal = analogRead(AN_THROT_PIN);  // keep an analog pin aslso as backup, if I2C magnetic is not going

  #elif defined (TLE493D_P3B6_A0)
    uint8_t buf[4];
    
    Wire1.requestFrom(ADDRESS, 4);
    for (uint8_t i = 0; i < 4; i++) {
      buf[i] = Wire1.read();
    }
    
    // Build 14-bit data for P3B6 A0
    int16_t X = (int16_t)((buf[0] << 8) | ((buf[1] & 0x3F) << 2)) >> 2;
    int16_t Y = (int16_t)((buf[2] << 8) | ((buf[3] & 0x3F) << 2)) >> 2;
    
    int16_t xSign = X < 0 ? -1 : 1;
    int16_t angle10degXY = 570 * (atan2(Y * xSign, X) + 1);
    retVal = angle10degXY;

  #elif defined (TLE493D_W2B6_A3)
    byte data[7];
    
    Wire1.requestFrom(ADDRESS, 7);
    for (byte i = 0; i < 7; i++) {
      data[i] = Wire1.read();
    }
    
    int16_t x = (data[0] << 4) | (data[4] >> 4);
    if (x >= 2048) x -= 4096;
    
    int16_t y = (data[1] << 4) | (data[4] & 0x0F);
    if (y >= 2048) y -= 4096;
    
    static int16_t x_avg = 0, y_avg = 0;
    x_avg = (x_avg * 3 + x) / 4;
    y_avg = (y_avg * 3 + y) / 4;
    
    float angleRad = atan2((float)y_avg, (float)x_avg);
    float angleDeg = angleRad * 180.0 / PI;
    if (angleDeg < 0) angleDeg += 360.0;
    
    retVal = (int16_t)(angleDeg * 10.0);
    
  #endif

  return retVal;
}


void HAL_PinSetup()
{
  pinMode(BUZZ_PIN, OUTPUT);     // Set BUZZ_PIN pin as an output
  pinMode(LED_BUILTIN, OUTPUT);  // Set ESP32 LED builtin pin as an output
  pinMode(BUTT_PIN, INPUT_PULLUP);// Set input pushbutton as input with pullup, so oyu con't need external resistor
  pinMode(ENCODER_BUTTON_PIN, INPUT_PULLUP);// Set input pushbutton as input with pullup, so oyu con't need external resistor
  
}

/*
  readVoltageDivider: read the voltage applied to an ADC by a voltage divider
  @param:AnalogInput , at which ADC input is connected the voltage divider
  @param:rvfbl low side resistor on the voltage divider
  @param:rvfbh high side resistor on the voltage divider
  @returns: voltage applied to the voltage divider [mV]
*/
uint16_t HAL_ReadVoltageDivider(int AnalogInput, uint32_t rvfbl, uint32_t rvfbh)
{
  uint32_t sum = 0;                   /* Sum of samples taken */
  unsigned char sample_count = 0;   /* Current sample number */
  uint32_t voltage = 0;               /* Calculated voltage */
  uint32_t ADCraw;

  /* Calculate the voltage, refVolt is the calibrated reference voltage in [V] */
  ADCraw = analogRead(AnalogInput) ; // 1023 
  voltage = (ACD_VOLTAGE_RANGE_MVOLTS * ADCraw) / ACD_RESOLUTION_STEPS;// voltage at teh ADC pin
  voltage = (voltage * (rvfbl + rvfbh)) / rvfbl; // voltage appied to the  voltage divider
  
  return voltage;
}

void sound(note_t note, int ms)
{
  ledcAttachChannel(BUZZ_PIN, 5000, 8, BUZZ_CHAN);
  ledcWriteNote(BUZZ_PIN, note, 7);
  delay (ms);
  ledcDetach(BUZZ_PIN);
}


// function onSound: generates "enabling" sound withthe buzzer. E.G. use when the device wakes up
void offSound()
{ 
  sound(NOTE_E, 60);
  delay(60);// pause between each sound
  sound(NOTE_C, 60);  
}


// function offSound: generates "disabling" sound. E.G. use when battery is detached
void onSound()
{ 
  sound(NOTE_C, 30);
  sound(NOTE_E, 30);
}


// function offSound: generates "disabling" sound. E.G. use when battery is detached
void calibSound()
{ 
  sound(NOTE_C, 60);
  delay(60);// pause between each sound
  sound(NOTE_G, 60);  
  delay(60);// pause between each sound
  sound(NOTE_A, 60);  
}

// function keySound: generates key pressed sound
void keySound()
{ 
  sound(NOTE_D, KEY_SOUND_MS);
}