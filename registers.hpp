#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <array>
#include <stdlib.h>
#include "ardtype.hpp"

#define DIGITAL_PIN_NUMBER 32
#define ANALOG_PIN_NUMBER 8

extern std::array<int, DIGITAL_PIN_NUMBER> digital_pin_register;
extern std::array<int, ANALOG_PIN_NUMBER> analog_pin_register;
extern std::array<PinMode, DIGITAL_PIN_NUMBER> digital_pin_mode_register;
extern std::array<PinMode, ANALOG_PIN_NUMBER> analog_pin_mode_register;

#endif // REGISTERS_HPP
