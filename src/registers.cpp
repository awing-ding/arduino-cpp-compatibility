/**
 * @file registers.cpp
 *
 * @brief Registers definition
 *
 * This file contains the definitions for the global registers used to simulate
 * the Arduino pins.
 */
#include "registers.hpp"
#include <array>

namespace arduinoTest {
std::array<int, DIGITAL_PIN_NUMBER> digital_pin_register = {0};
std::array<int, ANALOG_PIN_NUMBER> analog_pin_register = {0};
std::array<PinMode, DIGITAL_PIN_NUMBER> digital_pin_mode_register = {OUTPUT};
std::array<PinMode, ANALOG_PIN_NUMBER> analog_pin_mode_register = {OUTPUT};
}
