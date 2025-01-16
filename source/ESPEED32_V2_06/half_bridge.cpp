/*********************************************************************************************************************/
/*------------------------------------------------------Includes-----------------------------------------------------*/
/*********************************************************************************************************************/
#include "half_bridge.h"

using namespace btn99x0;

/*********************************************************************************************************************/
/*-------------------------------------------------Private variables-------------------------------------------------*/
/*********************************************************************************************************************/


/* 
  The half bridge constructor requires the following parameters:
  The chip variant, The pin assignment for its 3 signals, The ADC diagnostic pin hardware configuration
*/
ic_variant_t ic_variant = IC_VARIANT_BTN9990LV;

io_pins_t io_pins =
{
    .analog = HB_AN_PIN,
    .input = HB_IN_PIN,
    .inhibit = HB_INH_PIN
};

hw_conf_t hw_conf =
{
    .sense_current_resistor_ohms = 2000,
    .adc_voltage_range_volts = ACD_VOLTAGE_RANGE_MVOLTS/1000,
    .adc_resolution_steps    = ACD_RESOLUTION_STEPS
};

/* Half Bridge global instance */
HalfBridge half_bridge(ic_variant, io_pins, hw_conf); //  With all the required parameters we can create the half bridge instance of BTN99x0 device

/*********************************************************************************************************************/
/*---------------------------------------------Function Implementations----------------------------------------------*/
/*********************************************************************************************************************/
void HalfBridge_Setup()
{
  half_bridge.begin(); 
  half_bridge.set_slew_rate(SLEW_RATE_LEVEL_7);
  /** Set the dk experimental value to 50000 (previously measure for our setup) Also for set_ktis() could be called here. how to measure this dk experimentally? */
  half_bridge.set_dk(50000);

  HAL_InitHW();
}
void HalfBridge_SetupFabio()
{
  //half_bridge.begin(); DEBUG, removed, ttakes 10ms, used to calculate current resisto
  half_bridge.set_slew_rate(SLEW_RATE_LEVEL_7);
  /** Set the dk experimental value to 50000 (previously measure for our setup) Also for set_ktis() could be called here. how to measure this dk experimentally? */
  half_bridge.set_dk(50000);

  HAL_InitHW();
}


void HalfBridge_SetPwmDrag(uint8_t duty_pct, uint8_t drag_pct)
{
  half_bridge.set_pwm_drag(duty_pct, drag_pct);
}


void HalfBridge_Enable()
{
  half_bridge.enable();
}


void HalfBridge_TestMotor()
{
  half_bridge.set_pwm_drag(100,0);// go to full power
  delay(300);  
  half_bridge.set_pwm_drag(0,0);// let the motor spin with his inertia
  delay(1000);  
  half_bridge.set_pwm_drag(50,100);// request output duty plus some drag brake 
  delay(300);  
  half_bridge.set_pwm_drag(0,100);// request output duty plus some drag brake 
  delay(1000);  
}