#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <chrono>
#include <array>

#include "registers.hpp"
#include "test_api.hpp"





int TestApi::SetModeDigital(int pin, PinMode mode) {
    if (pin < 0) return -1;
    if (pin >= DIGITAL_PIN_NUMBER) return -1;
    digital_pin_mode_register[pin] = mode;
    return 0;
}
int TestApi::SetModeAnalog(int pin, PinMode mode) {
    if (pin >= ANALOG_PIN_NUMBER) return -1;
    analog_pin_mode_register[std::abs(pin)] = mode;
    return 0;
}
int TestApi::EditDigitalPin(int pin, int value) {
    if (pin < 0) return -1;
    if (pin >= DIGITAL_PIN_NUMBER) return -1;
    digital_pin_register[pin] = value;
    return 0;
}
int TestApi::EditAnalogPin(int pin, int value) {
    pin = std::abs(pin) - 1;
    if (pin >= ANALOG_PIN_NUMBER) return -1;
    analog_pin_register[std::abs(pin)] = value;
    return 0;
}
int TestApi::ReadDigitalPin(int pin) {
    if (pin < 0) return -1;
    if (pin >= DIGITAL_PIN_NUMBER) return -1;
    return digital_pin_register[pin];
}
int TestApi::ReadAnalogPin(int pin) {
    pin = std::abs(pin) - 1;
    if (pin >= ANALOG_PIN_NUMBER) return -1;
    return analog_pin_register[std::abs(pin)];
}

void logRegisters(){
    std::ofstream outfile("registers.log");

    for (int8_t i = 0; i < DIGITAL_PIN_NUMBER; i++) {
        outfile << "digital_pin_register[" << (int)i << "] = " << digital_pin_register[i] << std::endl;
    }
    outfile << "##################################################" <<std::endl;
    for (int8_t i = 0; i < DIGITAL_PIN_NUMBER; i++) {
        outfile << "digital_pin_mode_register[" << (int)i << "] = " << digital_pin_mode_register[i] << std::endl;
    }
    outfile << "##################################################" <<std::endl;
    outfile << "##################################################" <<std::endl;
    for (int8_t i = 0; i < ANALOG_PIN_NUMBER; i++) {
        outfile << "analog_pin_register[" << (int)i << "] = " << analog_pin_register[i] << std::endl;
    }
    outfile << "##################################################" <<std::endl;
    for (int8_t i = 0; i < ANALOG_PIN_NUMBER; i++) {
        outfile << "analog_pin_mode_register[" << (int)i << "] = " << analog_pin_mode_register[i] << std::endl;
    }
}

void log(char const * errorMsg){
    std::ofstream outfile("trace.log");
    outfile << errorMsg << std::endl;
    logRegisters();
}

const auto Cstart = std::chrono::system_clock::now();

void logVar(int pin){
    if (pin < 0 && std::abs(pin) - 1 > 8) {
        log("invalid analog pin id");
        fprintf(stderr, "invalid analog pin id (pin = %d)\n", pin);
        throw std::exception();
    }
    std::ofstream outfile("stats.log", std::ios::app);
    int pinValue = (pin < 0) ? analog_pin_register[std::abs(pin) - 1] : digital_pin_register[pin];
    outfile << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - Cstart).count() << "," << ((pin < 0) ? 'A' : '\0') << ((pin < 0) ? std::abs(pin +1) : pin) << "," << pinValue << std::endl;
}





