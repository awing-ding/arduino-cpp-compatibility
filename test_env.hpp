/**
 * @file test_env.hpp
 *
 * @brief Arduino compatibility
 *
 * Thies headers contains the declarations for the global functions use to 
 * simulate the Arduino environment.
 */
#ifndef ARDUINO_TEST_ENV_HPP
#define ARDUINO_TEST_ENV_HPP

#include "registers.hpp"
#include "ardtype.hpp"

int digitalWrite(int pin, int value);
int digitalRead(int pin);
int analogWrite(int pin, int value);
int analogRead(int pin);
int delay(int ms);
int delayMicroseconds(int us);
int pinMode(int pin, PinMode mode);
void logRegisters();
void log(char const * message);
void logVar(int pin);
long map(long x, long in_min, long in_max, long out_min, long out_max);

/**
 * @brief Arduino Serial compatibility
 *
 * Simulate some of the functionnality of the Arduino Serial class
 */
struct serial { 
    void begin(int baud);
    void print(char const * message);
    void println(char const * message);
    void end();
};

int millis();
int micros();

#endif
