/*
 * ArborParameters.c
 *
 *  Created on: Aug 17, 2023
 *      Author: andre
 */

#define _USE_MATH_DEFINES

#include "ArborParameters.h"
#include "DRV8825_Stepper.h"
#include "CoilWinderUtils.h"
#include "CoilParameters.h"
#include <math.h>

int Arbor_Init(ArborParameters_t* arbor, DRV8825_Stepper_t* driver,  uint32_t surface_speed_mm_per_sec,  int steps_per_rev) {
	if(steps_per_rev < 0)
		return -1;

	arbor->driver = driver;
	arbor->steps_per_rev = steps_per_rev;
	arbor->surface_speed_mm_per_sec = surface_speed_mm_per_sec;

	return 0;
}



int Arbor_SetSpeed(ArborParameters_t* arbor, int surface_speed_mm_per_sec) {
	if(surface_speed_mm_per_sec < 0)
		return -1;

	arbor->surface_speed_mm_per_sec = surface_speed_mm_per_sec;

	return 0;
}

void Arbor_SingleRevolution(ArborParameters_t* arbor, CoilParameters_t* coil) {

	uint32_t surface_speed_step_delay_us = (2 * M_PI * (Coil_getCoilDiam_10um(arbor->coil) / 200.0) * 1000000) / (arbor->steps_per_rev * arbor->surface_speed_mm_per_sec);

	uint32_t delay_iterations = us_to_iters(surface_speed_step_delay_us);

	for (int steps = 0; steps < arbor->steps_per_rev; steps++) {
		DRV8825_QuickStep(arbor->driver, delay_iterations);
	}
}


void Arbor_Start(ArborParameters_t* arbor) {
	DRV8825_Wake(arbor->driver);
	DRV8825_Enable(arbor->driver);
	DRV8825_SetDirection(arbor->driver, Forward);
}
void Arbor_End(ArborParameters_t* arbor) {
	DRV8825_Sleep(arbor->driver);
	DRV8825_Disable(arbor->driver);
}
