/**
 * @file test_api.cpp
 *
 * @brief Arduino API
 *
 * This file contains the logic for the library to use registers and log 
 * variables.
 */
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <chrono>
#include <array>

#include "registers.hpp"
#include "test_api.hpp"


/**
 * the logic to set the mode of digital pins
 *   - return -1 if the pin is invalid
 *   - modify the mode register of the corresponding pin
 * @param pin the pin to modify
 * @param mode the mode to set
 * @return 0 if success, -1 if failure
 */
int TestApi::SetModeDigital(int pin, PinMode mode) {
    if (pin < 0) return -1;
    if (pin >= DIGITAL_PIN_NUMBER) return -1;
    digital_pin_mode_register[pin] = mode;
    return 0;
}
/**
 * the logic to set the mode of analog pins
 *  - return -1 if the pin is invalid
 *  - modify the mode register of the corresponding pin
 * @param pin the pin to modify
 * @param mode the mode to set
 * @return 0 if success, -1 if failure
 */
int TestApi::SetModeAnalog(int pin, PinMode mode) {
    if (pin >= ANALOG_PIN_NUMBER) return -1;
    analog_pin_mode_register[std::abs(pin)] = mode;
    return 0;
}
/**
 * the logic to set the value of digital pins
 *  - return -1 if the pin is invalid
 *  - modify the value register of the corresponding pin
 * @param pin the pin to modify
 * @param value the value to set
 * @return 0 if success, -1 if failure
 */
int TestApi::EditDigitalPin(int pin, int value) {
    if (pin < 0) return -1;
    if (pin >= DIGITAL_PIN_NUMBER) return -1;
    digital_pin_register[pin] = value;
    return 0;
}
/**
 * the logic to set the value of analog pins
 *  - return -1 if the pin is invalid
 *  - modify the value register of the corresponding pin
 * @param pin the pin to modify
 * @param value the value to set
 * @return 0 if success, -1 if failure
 */
int TestApi::EditAnalogPin(int pin, int value) {
    pin = std::abs(pin) - 1;
    if (pin >= ANALOG_PIN_NUMBER) return -1;
    analog_pin_register[std::abs(pin)] = value;
    return 0;
}
/**
 * the logic to read the value of digital pins
 *  - return -1 if the pin is invalid
 *  - return the value register of the corresponding pin
 * @param pin the pin to read from
 * @return the value of the pin
 */
int TestApi::ReadDigitalPin(int pin) {
    if (pin < 0) return -1;
    if (pin >= DIGITAL_PIN_NUMBER) return -1;
    return digital_pin_register[pin];
}
/**
 * the logic to read the value of analog pins
 *  - return -1 if the pin is invalid
 *  - return the value register of the corresponding pin
 * @param pin the pin to read from
 * @return the value of the pin
 */
int TestApi::ReadAnalogPin(int pin) {
    pin = std::abs(pin) - 1;
    if (pin >= ANALOG_PIN_NUMBER) return -1;
    return analog_pin_register[std::abs(pin)];
}

/**
 * print all the registers to registers.log
 *   - create the file if doesn't exist
 *   - overwrite the file if it exists
 */
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

/**
 * print a message to trace.log
 *   - create the file if doesn't exist
 *   - overwrite the file if it exists
 * @param message the message to print
 */
void log(char const * message){
    std::ofstream outfile("trace.log");
    outfile << message << std::endl;
    logRegisters();
}

/**< starting timer for logging*/
const auto Cstart = std::chrono::system_clock::now();

/**
 * write a pin value to stats.log
 *  - create the file if doesn't exist
 *  - append to the file if it exists
 *  - throw an exception if the pin is invalid
 *  - it is write as : time,pin,value
 * @param pin the pin to log
 */
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





