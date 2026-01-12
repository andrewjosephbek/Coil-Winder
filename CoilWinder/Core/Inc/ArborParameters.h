/*
 * ArborParameters.h
 *
 *  Created on: Aug 17, 2023
 *      Author: andre
 */
#include "stm32l4xx_hal.h"
#include "DRV8825_Stepper.h"
#include "CoilParameters.h"

/**
 * @brief
 * Stores info about an "arbor" assembly (the belt driven assembly)
*/
typedef struct arbor_info {
	DRV8825_Stepper_t* driver;			// Stepper driver associated with this eye
	CoilParameters_t* coil;

	uint32_t steps_per_rev;				// Number of rising edges on the DRV8825 step line required to complete a full 360 degree rotation of the eye
	uint32_t surface_speed_mm_per_sec;	// Speed of the arbor in mm/sec


} ArborParameters_t;

/**
 * @brief
 * Initializes an arbor object
 *
 * @param driver The motor driver associated  with the arbor
 * @param steps_per_rev Number of rising edges on the DRV8825 step line required to complete a full 360 degree rotation of the arbor
 */
int Arbor_Init(ArborParameters_t* arbor, DRV8825_Stepper_t* driver,  uint32_t surface_speed_mm_per_sec,  int steps_per_rev);

/**
 * @brief
 * Sets the Arbors speed (in mm/s)
 *
 * @returns
 * returns 0 if the set operation completed
 * returns -1 if the surface_speed_mm_per_sec is negative
 */
int Arbor_SetSpeed(ArborParameters_t* arbor, int surface_speed_mm_per_sec);

/**
 * @brief
 * Executes a single turn of the arbor
 */
void Arbor_SingleRevolution(ArborParameters_t* arbor, CoilParameters_t* coil);

/**
 * @brief
 * Wakes and enables the arbor motor, sets its direction to forward.
 */
void Arbor_Start(ArborParameters_t* arbor);

/**
 * @brief
 * Sleeps and disables the arbor motor
 */
void Arbor_End(ArborParameters_t* arbor);
