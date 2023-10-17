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

namespace arduinoTest {

int digitalWrite(int pin, int value);
int digitalRead(int pin);
int analogWrite(int pin, int value);
int analogRead(int pin);
int delay(int ms);
int delayMicroseconds(int us);
int pinMode(int pin, PinMode mode);

long map(long x, long in_min, long in_max, long out_min, long out_max);
//long long abs(long long x);
double constrains(double x, double min, double max);
double max(double x, double y);
double min(double x, double y);
double pow(double x, double y);
double sq(double x);
double sqrt(double x);

double cos(double x);
double sin(double x);
double tan(double x);

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

}

#endif
