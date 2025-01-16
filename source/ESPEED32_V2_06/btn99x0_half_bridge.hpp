/**
 * @file        btn99x0_half_bridge.hpp
 * @brief       BTN99x0 Half Bridge API
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BTN99X0_HALF_BRIDGE_HPP_
#define BTN99X0_HALF_BRIDGE_HPP_

#include "Arduino.h"
#include "btn99x0_types.hpp"

/**
 * @addtogroup btn99x0_hb
 * @{
 */

namespace btn99x0
{
    class HalfBridge
    {
        public:

            HalfBridge(ic_variant_t ic_variant, io_pins_t io_pins, hw_conf_t hw_conf);
            ~HalfBridge();

            /* Control */
            void begin();
            void disable();
            void enable();

            /* Configuration */
            void set_pwm(uint8_t duty);
            void set_pwm_in_percentage(uint8_t duty_in_pct);
            void set_pwm_inh_percentage(uint8_t duty_in_pct);
            void set_pwm_drag(uint8_t duty_in_pct,uint8_t drag_pct);
            
            uint16_t set_slew_rate(slew_rate_level_t sr_level);
            /* Experimental value setting */
            void set_ktis(float ktis_amps_per_kelvin);
            void set_dk(uint16_t dk);

            /* Diagnosis */
            double get_load_current_in_amps();
            double get_temperature_in_kelvin();
            uint16_t get_diagnosis();

        private:

            static constexpr float fault_current_amps = 0.00251;                /**< Fault current threshold in amperes */
            static const ic_experimental_const_t btn9970lv_typical_exp_const;   /**< BTN9970LV typical experimental constants */
            static const ic_experimental_const_t btn9990lv_typical_exp_const;   /**< BTN9990LV typical experimental constants */

            io_pins_t io_pins;
            ic_experimental_const_t exp_const;
            hw_conf_t hw_conf;

            /* Inhibit value tracking for special functions state machine */
            uint8_t inhibit_pin_value;
            void set_inhibit_pin(uint8_t value);

            double calculate_current_at_sense_resistor_in_amps();
            void calculate_sense_resistor_offset_current();
            ic_experimental_const_t get_typical_experimental_constants(ic_variant_t ic_variant);

    };
}

/** @} */

#endif /* BTN99X0_HALF_BRIDGE_HPP_ */