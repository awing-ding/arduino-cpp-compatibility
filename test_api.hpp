#ifndef TEST_API_HPP
#define TEST_API_HPP
#include <stdlib.h>

#include "registers.hpp"
#include "ardtype.hpp"

#define DIGITAL_PIN_NUMBER 32
#define ANALOG_PIN_NUMBER 8

struct TestApi {
    static int init();
    static int SetModeDigital(int pin, PinMode mode);
    static int SetModeAnalog(int pin, PinMode mode);
    static int EditDigitalPin(int pin, int value);
    static int EditAnalogPin(int pin, int value);
    static int ReadDigitalPin(int pin);
    static int ReadAnalogPin(int pin);
    static const int8_t digitalPinNumber = DIGITAL_PIN_NUMBER;
    static const int8_t analogPinNumber = ANALOG_PIN_NUMBER;
};

void logRegisters();
void log(char const * message);
void logVar(int pin);

#endif // TEST_API_HPP
