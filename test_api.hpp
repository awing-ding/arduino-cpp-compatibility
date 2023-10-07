/**
 * @file test_api.hpp
 *
 * @brief Test API header
 *
 * This header contains the declarations for the test API.
 */
#ifndef TEST_API_HPP
#define TEST_API_HPP
#include <stdlib.h>

#include "registers.hpp"
#include "ardtype.hpp"

struct TestApi {
    static int SetModeDigital(int pin, PinMode mode);
    static int SetModeAnalog(int pin, PinMode mode);
    static int EditDigitalPin(int pin, int value);
    static int EditAnalogPin(int pin, int value);
    static int ReadDigitalPin(int pin);
    static int ReadAnalogPin(int pin);
    static const int8_t digitalPinNumber = DIGITAL_PIN_NUMBER; /**< the number of digital pins */
    static const int8_t analogPinNumber = ANALOG_PIN_NUMBER; /**< the number of analog pins */
};

void logRegisters();
void log(char const * message);
void logVar(int pin);

#endif // TEST_API_HPP
