#include "test_env.hpp"
#include "test_api.hpp"
#include "registers.hpp"


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <thread>

int digitalWrite(int pin, int value) {
    if (pin < 0) {
        log("trying to modify invalid pin\n");
        fprintf(stderr, "trying to modify invalid pin (%d)\n", pin);
        throw std::exception();
    }
    if (digital_pin_mode_register[pin] == INPUT) {
        log("trying to write to input pin\n");
        fprintf(stderr, "trying to write to input pin (%d), registers dumped\n", pin);
        logRegisters();
        throw std::exception();
    }
    digital_pin_register[pin] = value;
    return 0;
}

int digitalRead(int pin) {
    if (pin < 0) {
        log("trying to modify invalid pin\n");
        fprintf(stderr, "trying to modify invalid pin (%d)\n", pin);
        throw std::exception();
    }
    if (digital_pin_mode_register[pin] == OUTPUT) {
        log("trying to read from output pin\n");
        fprintf(stderr, "trying to read from output pin (%d), registers dumped\n", pin);
        logRegisters();
        throw std::exception();
    }
    return digital_pin_register[pin];
}

int analogWrite(int pin, int value) {
    pin = std::abs(pin) - 1;
    if (pin > 8 ) {
        log("trying to modify invalid pin\n");
        fprintf(stderr, "trying to modify invalid pin (A%d)\n", pin);
        throw std::exception();
    }
    if (digital_pin_mode_register[pin] == INPUT) {
        log("trying to write to input pin\n");
        fprintf(stderr, "trying to write to input pin (A%d), registers dumped\n", pin);
        throw std::exception();
    }
    analog_pin_register[pin] = value;
    return 0;
}

int analogRead(int pin) {
    pin = std::abs(pin) - 1;
    if (pin > 8) {
        log("trying to modify invalid pin\n");
        fprintf(stderr, "trying to modify invalid pin (A%d)\n", pin);
        throw std::exception();
    }
    if (digital_pin_mode_register[pin] == OUTPUT) {
        log("trying to read from output pin\n");
        fprintf(stderr, "trying to read from output pin (A%d), registers dumped\n", pin);
        throw std::exception();
    }
    return analog_pin_register[pin];
}

int delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    return 0;
}

int delayMicroseconds(int us) {
    std::this_thread::sleep_for(std::chrono::microseconds(us));
    return 0;
}

int pinMode(int pin, PinMode mode) {
    if (pin < 0){
        TestApi::SetModeAnalog(std::abs(pin) - 1, mode);
    }
    else TestApi::SetModeDigital(pin, mode);
    return 0;
}

long map(long x, long in_min, long in_max, long out_min, long out_max){ 
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void serial::print(char const * message) {
    log(message);
}
void serial::println(char const * message) {
    log(message);
}
void serial::begin(int baud) {
}
void serial::end(){
}

serial Serial = serial();

const auto start = std::chrono::system_clock::now();

int millis(){
    const auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int micros(){
    const auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}
