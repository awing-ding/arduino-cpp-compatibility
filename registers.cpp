#include "registers.hpp"
#include <array>

std::array<int, DIGITAL_PIN_NUMBER> digital_pin_register = {0};
std::array<int, ANALOG_PIN_NUMBER> analog_pin_register = {0};
std::array<PinMode, DIGITAL_PIN_NUMBER> digital_pin_mode_register = {OUTPUT};
std::array<PinMode, ANALOG_PIN_NUMBER> analog_pin_mode_register = {OUTPUT};

/*
bool initRegisters(){
    for (int i = 0; i < ANALOG_PIN_NUMBER; i++){
        analog_pin_register[i] = 0;
        analog_pin_mode_register[i] = INPUT;
    }
    for (int i = 0; i < DIGITAL_PIN_NUMBER; i++){
        digital_pin_register[i] = 0;
        digital_pin_mode_register[i] = INPUT;
    }
    return 0;
}

bool isInit = !initRegisters();*/



