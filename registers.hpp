/**
 * @file registers.hpp
 *
 * @brief Registers declaration
 *
 * This header contains the declarations for the global registers used to
 * simulate the Arduino pins you can here change the number of pin to match
 * your config.
 */
#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <array>
#include <stdlib.h>
#include "ardtype.hpp"

#define DIGITAL_PIN_NUMBER 32 /**< the number of digital pins */
#define ANALOG_PIN_NUMBER 8 /**< the number of analog pins, cannot be set higher than 9 */

extern std::array<int, DIGITAL_PIN_NUMBER> digital_pin_register; /**< the register for the value of the digital pins */
extern std::array<int, ANALOG_PIN_NUMBER> analog_pin_register; /**< the register for the value of the analog pins */
extern std::array<PinMode, DIGITAL_PIN_NUMBER> digital_pin_mode_register; /**< the register for the mode of the digital pins */
extern std::array<PinMode, ANALOG_PIN_NUMBER> analog_pin_mode_register; /**< the register for the mode of the analog pins */

#endif // REGISTERS_HPP
