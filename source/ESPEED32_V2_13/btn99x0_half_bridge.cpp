/**
 * @file        btn99x0_half_bridge.cpp
 * @brief       BTN99x0 Half Bridge API
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "btn99x0_half_bridge.hpp"
#include "HAL.h" // needed to change PWM frequency on motor control

using namespace btn99x0;

/**
 *
 */
const ic_experimental_const_t HalfBridge::btn9970lv_typical_exp_const =
{
    3.72e-6,
    40000,
    0
};

const ic_experimental_const_t HalfBridge::btn9990lv_typical_exp_const =
{
    3.72e-6,
    50000,
    0
};

/**
 * @brief       BTN99x0 Half Bridge Constructor
 *
 * @param[in]   ic_variant  IC product variant
 * @param[in]   io_pins     IC controller connected pins (inhibit, input and current sense)
 * @param[in]   hw_conf     Hardware configuration and experimental parameters
 * @pre         None
 */
HalfBridge::HalfBridge(ic_variant_t ic_variant, io_pins_t io_pins, hw_conf_t hw_conf)
:
io_pins(io_pins),
exp_const(get_typical_experimental_constants(ic_variant)),
hw_conf(hw_conf)
{
    pinMode(io_pins.analog, INPUT);
    pinMode(io_pins.input, OUTPUT);
    pinMode(io_pins.inhibit, OUTPUT);
}

/**
 * @brief       BTN99x0 Half Bridge Destructor
 * @pre         None
 */
HalfBridge::~HalfBridge()
{

}

/**
 * @brief       Initializes the device
 * @details     Calculates the offset current on the current
 *              sense ADC input port
 * @pre         None
 */
void HalfBridge::begin()
{
    delay(10);
    calculate_sense_resistor_offset_current();

    /* Initialize inhibit and input to LOW */
//    set_inhibit_pin(LOW);
//    digitalWrite(io_pins.input, LOW);
}

/**
 * @brief       Enables the device output
 * @details     Sets the inhibit pin high
 * @pre         None
 */
void HalfBridge::enable()
{
    set_inhibit_pin(HIGH);
}

/**
 * @brief       Disables the device output setting it to high impedance
 * @details     Set the inhibit pin low
 * @pre         None
 */
void HalfBridge::disable()
{
    set_inhibit_pin(LOW);
}

/**
 * @brief       Sets a PWM signal in the output for the given duty cycle
 * @details     The PWM signal is provided at the half-bridge input pin
 * @param[in]   duty Duty cycle in range from 0 to 255
 * @pre         None
 */
void HalfBridge::set_pwm(uint8_t duty)
{
    analogWrite(io_pins.input, duty);
}

/**
 * @brief       Sets a PWM signal in the output for the given duty cycle
 * @details     Provides at the half-bridge IN pin the requested duty, the INHIBIT pin is kept high
 * @param[in]   duty_in_pct Duty cycle in percentage from 0 % to 100 %
 * @pre         None
 */
void HalfBridge::set_pwm_in_percentage(uint8_t duty_in_pct)
{
    uint8_t duty8bit;
    if((duty_in_pct <= 100) & (duty_in_pct >= 0))
    {
      duty8bit = duty_in_pct*255/100;
      HALanalogWrite(THR_IN_PWM_CHAN, duty8bit);
      HALanalogWrite(THR_INH_PWM_CHAN, 255);
    };
}

/**
 * @brief       produces a PWM asyncronous (only High side) at the Half bridge output
 * @details     Provides at the half-bridge inhibit pin the requested duty, the IN pin is kept high
 * @param[in]   duty_in_pct Duty cycle in percentage from 0 % to 100 %
 * @pre         None
 */
void HalfBridge::set_pwm_inh_percentage(uint8_t duty_in_pct)
{
  uint8_t duty8bit;
  if((duty_in_pct <= 100) & (duty_in_pct >= 0))
  {
    duty8bit = duty_in_pct*255/100;
    HALanalogWrite(THR_IN_PWM_CHAN, 255);
    HALanalogWrite(THR_INH_PWM_CHAN, duty8bit);
  };
}



/**
 * @brief       produces a PWM asyncronous (only High side) at the Half bridge output
 * @details     The PWM signal is provided at the half-bridge inhibit pin, the in pin is kept high
 * @param[in]   duty_in_pct Duty cycle in percentage from 0 % to 100 %
 * @pre         None
 */
void HalfBridge::set_pwm_drag(uint8_t duty_in_pct, uint8_t drag_pct)
{
  uint16_t drag8bit,duty8bit,inh8bit;
  
  duty_in_pct = constrain(duty_in_pct,0,100); // limit in put parameters to 0-100[%]
  drag_pct = constrain(drag_pct,0,100);
  
  duty8bit = ((uint16_t)duty_in_pct*255 )/100;

  drag8bit = ((uint16_t)drag_pct*255 )/100;

  inh8bit = (duty8bit + drag8bit);          //HBridge enable has to last for the high side on phase+ drag (where Low side will be activated)
  
  inh8bit = constrain(inh8bit,0,255);

  HALanalogWrite(THR_IN_PWM_CHAN, duty8bit);

  HALanalogWrite(THR_INH_PWM_CHAN, inh8bit);

}



/**
 * @brief       Sets slew rate level
 * @details     The slew level is configured by making a pulse sequence
 *              at the input pin while the inhibit pin is set to low.
 *              The number of pulses determine the level of the slew
 *              rate.
 *              Find more information in the section "4.4.2 Adjustable
 *              slew rate" in page 23 of the BTN99x0 datasheet (Rev. 1.0)
 * @param[in]   re_level Slew rate level
 * @pre         begin() and disable() if the half bridge has been previously enabled
 * @warning     The current operation requires the device to be in slew rate selection
 *              mode, meaning the INH pin to be set to low.
 *              The function operates the INPUT pin, any
 *              PWM value previously configured will be overwritten
 * @return      Error code
 * @retval      INVALID_OPERATION_ERROR if the half bridge inhibit pin is not LOW
 * @retval      NO_ERROR if the half-bridge is operating properly
 */
uint16_t HalfBridge::set_slew_rate(slew_rate_level_t sr_level)
{
    if(LOW != inhibit_pin_value)
    {
        return INVALID_OPERATION_ERROR;
    }

    /*
    pulses the input_pin pin
    */
    delayMicroseconds(5);
    for(uint8_t i = 0; i <= ((uint8_t)sr_level + 1); i++)
    {
        digitalWrite(io_pins.input, HIGH);
        delayMicroseconds(1);
        digitalWrite(io_pins.input, LOW);
    }
    delayMicroseconds(5);

    return NO_ERROR;
}

/**
 * @brief       Checks if there is any failure in the half-bridge
 * @details     Check if the current at the sense resistor is above
 *              the fault current threshold.
 *              Find more information about extended diagnosis
 *              functionalities in the datasheet
 * @return      Error code
 * @retval      FAULT_CURRENT_ERROR if error
 * @retval      NO_ERROR if the half-bridge is operating properly
 * @pre         begin()
 */
uint16_t HalfBridge::get_diagnosis()
{
    if(calculate_current_at_sense_resistor_in_amps() >= fault_current_amps)
    {
        return FAULT_CURRENT_ERROR;
    }

    return NO_ERROR;
}

/**
 * @brief       Sets the k_TIS constant
 * @details     The k_TIS constant is used to calculate the chip temperature.
 *              Find out more in the datasheet about how to experimentally
 *              measure the constant value for your system setup
 * @param[in]   ktis_amps_per_kelvin K_TIS experimental constant
 * @pre         None
 */
void HalfBridge::set_ktis(float ktis_amps_per_kelvin)
{
    exp_const.ktis_amps_per_kelvin = ktis_amps_per_kelvin;
}

/**
 * @brief       Sets the dk constant
 * @details     The dk constant is used to calculate the load current.
 *              Find out more in the datasheet about how to experimentally
 *              measure the constant value for your system setup
 * @param[in]   dk Differential current sense ratio
 * @pre         None
 */
void HalfBridge::set_dk(uint16_t dk)
{
    exp_const.dk = dk;
}

/**
 * @brief       Gets load current in amperes
 * @return      Load current in amperes
 * @pre         begin()
 */
double HalfBridge::get_load_current_in_amps()
{
    return ((exp_const.dk)*(calculate_current_at_sense_resistor_in_amps() - exp_const.sense_current_offset_amps));
}

/**
 * @brief       Gets the device temperature in kelvin
 * @pre         begin() and disable() if the half bridge has been previously enabled
 * @warning     The current operation requires the device to be in slew rate selection
 *              mode, meaning the INH pin to be set to low.
 *              The function operates the INPUT pin, any
 *              PWM value previously configured will be overwritten
 * @return      Temperature in kelvin
 * @retval      Negative value. INVALID_OPERATION_ERROR if the half bridge inhibit pin is not LOW
 */
double HalfBridge::get_temperature_in_kelvin()
{
    if(LOW != inhibit_pin_value)
    {
        return (double)INVALID_OPERATION_ERROR;
    }

    double chip_temperature;

    digitalWrite(io_pins.input, HIGH);
    delayMicroseconds(7);

    chip_temperature = (calculate_current_at_sense_resistor_in_amps())/exp_const.ktis_amps_per_kelvin;

    return chip_temperature;
}

/**
 * @brief       Set the inhibit pin to the given value
 * @details     Convenience function to store the actual value
 *              of the inhibit pin together with setting the pin
 * @param[in]   value Digital pin value. HIGH or LOW
 * @pre         None
 */
void HalfBridge::set_inhibit_pin(uint8_t value)
{
    inhibit_pin_value = value;
    digitalWrite(io_pins.inhibit, value);
}

/**
 * @brief       Calculates the current at the sense resistor in amperes
 * @return      Current in amperes
 * @pre         None
 */
double HalfBridge::calculate_current_at_sense_resistor_in_amps()
{
    double adc_volts_per_step = (hw_conf.adc_voltage_range_volts/hw_conf.adc_resolution_steps);
    double voltage_sense_resistor_volts = analogRead(io_pins.analog)*adc_volts_per_step;

    return voltage_sense_resistor_volts/hw_conf.sense_current_resistor_ohms;
}

/**
 * @brief       Calculates the offset current at the current sense ADC input
 * @details     Set the corresponding parameters of the experimental constant value set
 * @pre         None
 */
void HalfBridge::calculate_sense_resistor_offset_current(void)
{
    enable();
    digitalWrite(io_pins.input, LOW);

    delayMicroseconds(50);
    exp_const.sense_current_offset_amps = calculate_current_at_sense_resistor_in_amps();
    delayMicroseconds(5);

    disable();
}

/**
 * @brief       Gets the typical experimental constant set for a given half-bridge variant
 * @param[in]   ic_variant Half-bridge IC variant
 * @return      Experimental constants set
 * @pre         None
 */
ic_experimental_const_t HalfBridge::get_typical_experimental_constants(ic_variant_t ic_variant)
{
    switch(ic_variant)
    {
        case IC_VARIANT_BTN9970LV:
            return btn9970lv_typical_exp_const;
        break;

        case IC_VARIANT_BTN9990LV:
            return btn9990lv_typical_exp_const;
        break;

      default:
            return btn9990lv_typical_exp_const;
        break;

    }
}