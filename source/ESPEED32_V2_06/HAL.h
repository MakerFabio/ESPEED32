#ifndef HAL_H_
#define HAL_H_

/*********************************************************************************************************************/
/*------------------------------------------------------Includes-----------------------------------------------------*/
/*********************************************************************************************************************/
#include <Wire.h>
#include <Arduino.h>
/*********************************************************************************************************************/
/*-------------------------------------------------------Macros------------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************** HARDWARE DEFINITIONS ************************************************/

/******** DISPLAY ********/
#define MY_OLED     OLED_128x64
#define OLED_WIDTH  128
#define OLED_HEIGHT 64
#define USE_BACKBUFFER /* if your system doesn't have enough RAM for a back buffer, comment out this line */

/* SHUNT RESISTORS, VOLTAGE DIVIDERS, REFERENECE VOLTAGE */
#define RVIFBL 2200UL    // [Ohm]Vin ADC resistor divider, lower resistor
#define RVIFBH 10000UL   // [Ohm]Vin ADC resistor divider, upper resistor

/********** ADC **********/
#define THROTTLE_NORMALIZED         256
#define THROTTLE_DEADBAND_PERC      3  /* [%]percent of throtthe that is considered 100% or 0%, when the wiper is close to the travel edges */
#define THROTTLE_DEADBAND_NORM      ((THROTTLE_DEADBAND_PERC*THROTTLE_NORMALIZED)/100)
#define THROTTLE_NOISE_PERC         2
#define THROTTLE_NOISE_NORM         ((THROTTLE_NOISE_PERC*THROTTLE_NORMALIZED)/100)
#define ACD_RESOLUTION_STEPS 4095

#define VIN_CAL_SET 1200
#define VIN_CAL_READ 1108
#define ACD_VOLTAGE_RANGE_MVOLTS  (3300*VIN_CAL_SET/VIN_CAL_READ) // ADC voltage range calibrate d to actual read value

#define MAX_INT16            32767 // maximum raw value from a int16(used for throttle read raw calibration)
#define MIN_INT16            -32768 

/********** PWM **********/
#define THR_IN_PWM_CHAN   0     /* ESP32 has 16 channels which can generate 16 independent waveforms */
#define THR_INH_PWM_CHAN  1     /* ESP32 has 16 channels which can generate 16 independent waveforms */
#define BUZZ_CHAN         6     /* PWM channel used to generate tone on buzzer */ 
//#define THR_PWM_FREQ      5     /* kHz Recall that Arduino Uno is ~490 Hz. Official ESP32 example uses 5,000Hz */
#define THR_PWM_RES_BIT   8     /* We'll use same resolution as Uno (8 bits, 0-255) but ESP32 can go up to 16 bits */ 

/******** TRIGGER ********/
//#define AS5600_MAG  // DEFAULT WORKING
#define TLE493D_P3B6_A0   // Infineon TLE493D-P3B6 A0 variant (I2C address 0x5D)
//#define TLE493D_W2B6_A3     // Infineon TLE493D-W2B6 A3 variant (I2C address 0x44)
//#define AS5600L_MAG // similar to the AS5600, but 5600L has differnt address 
//#define ANALOG_TRIG  // define ANALOG_TRIG in case you are using potentiometer , or magnetic with simple analog output as trigger
//#define MT6701_MAG  // define MT6701_MAG if you are using a MT6701 magnetic sensor

#if defined (AS5600_MAG) || defined (AS5600L)
  #define THROTTLE_REV        1  /* if 1 the throttle is at full press when the ADC value is the minimum (inverted) */
#elif defined (MT6701_MAG)
  #define THROTTLE_REV        1  /* if 1 the throttle is at full press when the ADC value is the minimum */
#elif defined (ANALOG_TRIG)
  #define THROTTLE_REV        1  /* if 1 the throttle is at full press when the ADC value is the minimum */
#elif defined (TLE493D_P3B6_A0) || defined (TLE493D_W2B6_A3)
  #define THROTTLE_REV        0  /* if 1 the throttle is at full press when the ADC value is the minimum */
#endif

/******** EEPROM *********/
/* Deprecated */
/* No longer used since passing to Preferences.h library to store NVM data */
//#define EEPROM_INIT_WORD  0xFE /*dummy value used to check if user parameters has been written on the EEPROM at least once on VREG sketch (use different onother sketch type) */
//#define ADDR_EEPROM_INIT  0x00 /* address of INITIALization word in the EEPROM */
//#define ADDR_EEPROM_USER  0x04 /* address of user variables in the eeprom (just after initialization word) */
//#define EEPROM_SIZE       512

/******** OTHERS *********/
#define KEY_SOUND_MS      50
#define BUTTON_PRESSED    0

/************************************************** PIN DEFINITIONS **************************************************/

#define SDA0_PIN    21    /* HW I2C Number 1 SDA : Magnetic  */
#define SCL0_PIN    22    /* HW I2C Number 1 SCL : Magnetic */    
#define SDA1_PIN    33    /* HW I2C Number 1 SDA : OLED */
#define SCL1_PIN    32    /* HW I2C Number 1 SCL : OLED  */

#define RESET_PIN   -1    /* Set this to -1 to disable or the GPIO pin number connected to the reset line of your display if it requires an external reset */
#define OLED_ADDR   -1    /* Let OneBitDisplay figure out the display address */
//#define OLED_ADDR 0x3C //
#define FLIP180     0     /* Don't rotate the display */
#define INVERT_DISP 0     /* Don't invert the display */
#define USE_HW_I2C  1     /* HW I2C or Bit-Bang the I2C bus     */

/***** ANALOG PIN ******/
#define AN_VIN_DIV   36

/****** ENCODER PIN ******/
#define ENCODER_A_PIN      16 /* In our encoder is PIN S1 */
#define ENCODER_B_PIN      17 /* In our encoder is PIN S2 */
#define ENCODER_BUTTON_PIN 4  /* In our encoder is PIN KEY */
#define ENCODER_VCC_PIN    -1 /* 27 put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */
#define ENCODER_STEPS      4

/* MOTOR CURRENT & BEMF */
#define AN_MOT_BEMF   14 /* Motor back EMF sensig */
#define HB_AN_PIN     25
#define HB_IN_PIN     26 
#define HB_INH_PIN    27 /* debug place back 27, 2 is the LED */
#define LED_BUILTIN   2

/******* OTHER PIN *******/
#define BUTT_PIN   13   /* Button */
#define BUZZ_PIN   18   /* minislotESC V2.1 /

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void     HAL_InitHW();
uint16_t HAL_ReadVoltageDivider(int AnalogInput, uint32_t rvfbl, uint32_t rvfbh);
int16_t  HAL_ReadTriggerRaw();
void     HALanalogWrite (int PWMchan, int value);
void     HAL_PinSetup();
uint16_t HAL_AdcRawToPct(uint16_t raw, uint16_t min, uint16_t max, bool reverse);

void sound(note_t note,int ms);
void offSound();
void onSound();
void calibSound();
void keySound();

#endif