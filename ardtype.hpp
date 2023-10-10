/**
 * @file ardtype.hpp
 *
 * @brief Arduino types
 *
 * This header contains the declarations for the global types used in arduino
 * as INPUT/OUTPUT, HIGH/LOW, etc.
 */
#ifndef ARDTYPE_HPP
#define ARDTYPE_HPP

/**
 * @brief Pin mode
 *
 * This enum is used to define the mode of a pin.
 */
enum PinMode {
    INPUT, /**< the pin is in input mode (0) */
    OUTPUT, /**< the pin is in output mode (1) */
    INPUT_PULLUP = INPUT /**< the pin is in input mode with pullup resistor (0), as register represent electrical state and not logical state, it doesn't matter */
};

/**
 * @brief Digital pin value
 *
 * This enum is used to define the value of a digital pin.
 */
enum DigitalPinValue {
    LOW, /**< the pin is in low state (0) */
    HIGH /**< the pin is in high state (1) */
};

/**
 * @brief Analog pin value
 *
 * This enum is used to define the value of a analog pin.
 */
enum AnalogPin{
    A0 = -1,
    A1 = -2,
    A2 = -3,
    A3 = -4,
    A4 = -5,
    A5 = -6,
    A6 = -7,
    A7 = -8,
    A8 = -9,
};

#endif
