/**
 * @file test_env.cpp
 *
 * @brief Arduino compatibility
 *
 * This file contains the definitions for the global functions use to simulate
 * the Arduino environment.
 */
#include "test_env.hpp"
#include "test_api.hpp"
#include "registers.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>

namespace arduinoTest {
int LED_BUILTIN = 13; /**< Pin assigned to the builtin led */

/**
 * simulate the arduino digital write function
 *  - throws an exception if the pin is invalid
 *  - throws an exception if the pin is in input mode
 *
 * @param pin the pin to write to
 * @param value the value towrite
 * @return 0
 */
int digitalWrite(int pin, int value) {
    if (value != LOW && value != HIGH) {
        log("trying to write invalid value\n");
        fprintf(stderr, "\33[31mtrying to write invalid value (%d)\33[0m\n", value);
        throw std::exception();
    }
    if (pin < 0 || pin > DIGITAL_PIN_NUMBER - 1) {
        log("trying to modify invalid pin\n");
        fprintf(stderr, "\33[31m trying to modify invalid pin (%d)\33[0m\n", pin);
        throw std::exception();
    }
    if (digital_pin_mode_register[pin] == INPUT) {
        log("trying to write to input pin\n");
        fprintf(stderr, "\33[31m trying to write to input pin (%d), registers dumped\33[0m\n", pin);
        logRegisters();
        throw std::exception();
    }
    digital_pin_register[pin] = value;
    return 0;
}

/**
 * simulate the arduino digital read function
 *   - throws an exception if the pin is invalid
 *   - throws an exception if the pin is in output mode
 *
 * @param pin the pin to read from
 * @return the value of the pin
 */
int digitalRead(int pin) {
    if (pin < 0 || pin > DIGITAL_PIN_NUMBER - 1) {
        log("trying to modify invalid pin\n");
        fprintf(stderr, "\33[31mtrying to modify invalid pin (%d)\33[0m\n", pin);
        throw std::exception();
    }
    if (digital_pin_mode_register[pin] == OUTPUT) {
        log("trying to read from output pin\n");
        fprintf(stderr, "\33[31mtrying to read from output pin (%d), registers dumped\33[0m\n", pin);
        logRegisters();
        throw std::exception();
    }
    return digital_pin_register[pin];
}

/**
 * simulate the arduino analog write function
 *   - throws an exception if the pin is invalid
 *   - throws an exception if the pin is in input mode
 *
 * @param pin the pin to write to
 * @param value the value to write
 * @return 0
 */
int analogWrite(int pin, int value) {
    pin = std::abs(pin) - 1;
    if (pin > ANALOG_PIN_NUMBER - 1 || pin < 0) {
        log("trying to modify invalid pin\n");
        fprintf(stderr, "\33[31mtrying to modify invalid pin (A%d)\33[0m\n", pin);
        throw std::exception();
    }
    if (digital_pin_mode_register[pin] == INPUT) {
        log("trying to write to input pin\n");
        fprintf(stderr, "\33[31mtrying to write to input pin (A%d), registers dumped\33[0m\n", pin);
        throw std::exception();
    }
    analog_pin_register[pin] = value;
    return 0;
}

/**
 * simulate the arduino analog read function
 *   - throws an exception if the pin is invalid
 *   - throws an exception if the pin is in output mode
 *
 * @param pin the pin to read from
 * @return the value of the pin
 */
int analogRead(int pin) {
    pin = std::abs(pin) - 1;
    if (pin > ANALOG_PIN_NUMBER - 1 || pin < 0) {
        log("trying to modify invalid pin\n");
        fprintf(stderr, "\33[31mtrying to modify invalid pin (A%d)\33[0m\n", pin);
        throw std::exception();
    }
    if (digital_pin_mode_register[pin] == OUTPUT) {
        log("trying to read from output pin\n");
        fprintf(stderr, "\33[31mtrying to read from output pin (A%d), registers dumped\33[0m\n", pin);
        throw std::exception();
    }
    return analog_pin_register[pin];
}

/**
 * simulate the arduino delay function
 *   - sleeps for the given amount of time
 *
 * @param ms the amount of time to sleep in milliseconds
 * @return 0
 */
int delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    return 0;
}

/**
 * simulate the arduino delayMicroseconds function
 *   - sleeps for the given amount of time
 *
 * @param us the amount of time to sleep in microseconds
 * @return 0
 */
int delayMicroseconds(int us) {
    std::this_thread::sleep_for(std::chrono::microseconds(us));
    return 0;
}

/**
 * simulate the arduino pinMode function
 *   - throws an exception if the pin is invalid
 *
 * @param pin the pin to modify
 * @param mode the mode to set the pin to
 * @return 0
 */
int pinMode(int pin, PinMode mode) {
    if (pin < 0){
        TestApi::SetModeAnalog(std::abs(pin) - 1, mode);
    }
    else TestApi::SetModeDigital(pin, mode);
    return 0;
}

/**
 * simulate the arduino map function
 *  - maps a value from one range to another
 *
 * @param x the value to map
 * @param in_min the minimum value of the input range
 * @param in_max the maximum value of the input range
 * @param out_min the minimum value of the output range
 * @param out_max the maximum value of the output range
 * @return the mapped value
 */ 
long map(long x, long in_min, long in_max, long out_min, long out_max){ 
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * simulate the arduino constrain function
 *  - constrains a value to a given range
 *
 * @param x the value to constrain
 * @param min the minimum value of the range
 * @param max the maximum value of the range
 * @return the constrained value
 */
double constrain(double x, double min, double max){
    return x < min ? min : x > max ? max : x;
}
/**
 * simulate the arduino max function
 * - returns the maximum of two values
 *
 * @param x the first value
 * @param y the second value
 * @return the maximum of the two values
 */
double max(double x, double y){
    return x > y ? x : y;
}

/**
 * simulate the arduino min function
 * - returns the minimum of two values
 *
 * @param x the first value
 * @param y the second value
 * @return the minimum of the two values
 */
double min(double x, double y){
    return x < y ? x : y;
}

/**
 * simulate the arduino pow function
 * - returns the first value to the power of the second value
 *
 * @param x the first value
 * @param y the second value
 * @return the first value to the power of the second value
 */
double pow(double x, double y){
    return std::pow(x, y);
}

/**
 * simulate the arduino sq function
 * - returns the square of the given value
 *
 * @param x the value to square
 * @return the square of the given value
 */
double sq(double x){
    return x * x;
}

/**
 * simulate the arduino sqrt function
 * - returns the square root of the given value
 *
 * @param x the value to take the square root of
 * @return the square root of the given value
 */
double sqrt(double x){
    return std::sqrt(x);
}

/**
 * simulate the arduino cos function
 * - returns the cosine of the given value
 *
 * @param x the value to take the cosine of
 * @return the cosine of the given value
 */
double cos(double x){
    return std::cos(x);
}

/**
 * simulate the arduino sin function
 * - returns the sine of the given value
 *
 * @param x the value to take the sine of
 * @return the sine of the given value
 */
double sin(double x){
    return std::sin(x);
}

/**
 * simulate the arduino tan function
 * - returns the tangent of the given value
 *
 * @param x the value to take the tangent of
 * @return the tangent of the given value
 */
double tan(double x){
    return std::tan(x);
}

/**
 * simulate the arduino Serial.print method
 *  - prints the given message to trace.log
 *  - does not print a newline
 *  - does not support formatting
 *  - does not support multiple arguments
 *  - only supports strings
 */
void serial::print(char const * message) {
    log(message);
}

/**
 * simulate the arduino Serial.println method
 *  - prints the given message to trace.log
 *  - prints a newline
 *  - does not support formatting
 *  - does not support multiple arguments
 *  - only supports strings
 */
void serial::println(char const * message) {
    log(message);
}

/**
 * simulate the arduino Serial.begin method
 *  - does nothing as it's not needed on computer
 */
void serial::begin(int baud) {
}
/**
 * simulate the arduino Serial.end method
 *  - does nothing as it's not needed on computer
 */
void serial::end(){
}

/**< initialize the Serial object used in arduino*/
serial Serial = serial();

/**< initialize the start time for millis and micros*/
const auto start = std::chrono::system_clock::now();

/**
 * simulate the arduino millis function
 *  - returns the number of milliseconds since the program started
 *
 * @return the number of milliseconds since the program started
 */
int millis(){
    const auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

/**
 * simulate the arduino micros function
 *  - returns the number of microseconds since the program started
 *
 * @return the number of microseconds since the program started
 */
int micros(){
    const auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

}
