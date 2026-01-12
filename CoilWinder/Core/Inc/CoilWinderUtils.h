/*
 * utils.h
 *
 *  Created on: Aug 11, 2023
 *      Author: andre
 */

#ifndef INC_COILWINDERUTILS_H
#define INC_COILWINDERUTILS_H

#include "stm32l4xx_hal.h"
//UI CONSTANTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define UI_FIELD_OFFSET 11 //The number of spaces between a UI feild's title and value

#define UI_1_X 0								// The x position of UI element 1's title
#define UI_1_Y  0								// The y position of UI element 1's title and value

#define UI_2_X  0								// ... (see above)
#define UI_2_Y  1								// ...

#define UI_3_X  0
#define UI_3_Y  2

#define UI_4_X  0
#define UI_4_Y  3

#define UI_5_X  19								// The x position of UI element 5
#define UI_5_Y  3								// The y position of UI element 5

#define UI_1_MULT  5							// The increment added to UI element 1's value when quick press hold in enabled
#define UI_2_MULT  75							// ... (see above)
#define UI_3_MULT  10
#define UI_4_MULT  1

#define INT_BLANK_SIZE  8						// The number of spaces required to erase an integer value on the LCD
#define HALF_UINT_MAX 2147483645;				// Half of the the max possible integer that an unsigned 32 bit integer can store


//MECHANICHAL CONSTANTS ~~~~~~~~~~~~~~~~~~~~~~~

#define MICROSTEP_LEVEL 16						// The micro-step resolution the DRV8825 drivers currently set at
#define EYE_GEAR_REDUCTION  40					// Gear reduction of the eye stepper
#define ARBOR_GEAR_REDUCTION  3					// Gear reduction of the arbor stepper
#define STEPS_PER_REV  200						// Standard stepper resolution (steps per revolution)

#define ARBOR_STEPS  STEPS_PER_REV * ARBOR_GEAR_REDUCTION * MICROSTEP_LEVEL 	//Steps per revolution of the arbor
#define EYE_STEPS  STEPS_PER_REV * EYE_GEAR_REDUCTION * MICROSTEP_LEVEL			//Steps per revolution of the eye
#define EYE_LENGTH 52.75

//MISC CONSTANTS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define FIXED_POINT_PRECISION  2				// Position of the decimal point in fixed point numbers

//UTILITY FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
 * @brief
 * inserts a character into a string
 *
 * @param str the string to insert the char into
 * @param pos the array position of the inserted char
 * @param ch the character to insert
 *
 *
 * @returns
 * returns 0 if the insertion was completed
 * returns -1 if if the pos is out of bounds
 */
int str_insertChar(char * str, int pos, char ch);

/**
 * @brief
 * takes a string representation of an integer and multiplies it by 10^-(precision)
 *
 * @details
 * adds a decimal point and any necessary '0' characters, no precision is lost
 *
 * @param str the string to modify
 * @param precision the number of characters that should be behind the decimal point
 *
 * @returns
 * returns 0 if the modification was completed
 * returns -1 if precision is <= 0
 */
int integerStringToFixedPointString(char * str, int precision);

/**
 * @brief
 * takes the absolute value of a double
 *
 * @returns
 * returns the absolute value of num
 */
double double_abs(double num);

/**
 * @brief
 * delays execution by a set number of clock cycles
 *
 * @param iterations the number of clock cycles to delay by
 */
void delay_iterations(uint32_t iterations);

/**
 * @brief
 * returns the number of clock cycles to achieve a delay in execution equivalent to the @param microseconds time interval
 *
 * @note
 * value is approximate
 */
uint32_t us_to_iters(uint32_t microseconds);

#endif /* INC_COILWINDERUTILS_H_ */
