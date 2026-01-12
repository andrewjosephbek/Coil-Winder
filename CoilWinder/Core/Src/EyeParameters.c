
/*
 * EyeParameters.c
 *
 *  Created on: Aug 14, 2023
 *      Author: andre
 */
#define _USE_MATH_DEFINES

#include "EyeParameters.h"
#include <math.h>
#include <CoilWinderUtils.h>


int Eye_Init(EyeParameters_t* eye, DRV8825_Stepper_t* driver, double length_mm, double current_postion_mm, uint32_t steps_per_rev, GPIO_TypeDef* LIMIT_SW_Pin_Port, uint16_t LIMIT_SW_Pin) {

    if(current_postion_mm > (length_mm*2))
        return -1;

    eye->driver = driver;
	eye->length_mm = length_mm;
	eye->steps_per_rev = steps_per_rev;
    Eye_SetPosition(eye, current_postion_mm);
   
    eye->LIMIT_SW_Pin_Port = LIMIT_SW_Pin_Port;
    eye->LIMIT_SW_Pin = LIMIT_SW_Pin;


    return 0;

}



int Eye_SetPosition(EyeParameters_t* eye, double new_current_postion_mm)
{

	// Check that inputs are good
	if(new_current_postion_mm > (eye->length_mm))
		return -1;

	// Check that inputs are good
	if(new_current_postion_mm < (-1*eye->length_mm))
		return -1;


	// Set the position
	eye->current_postion_mm = new_current_postion_mm;

	// Calculate the corresponding angle

	if(eye->current_postion_mm <= 0) {

		eye->current_angle_radians = acos( double_abs(eye->current_postion_mm) / eye->length_mm );

	} else if(eye->current_postion_mm > 0) {

		eye->current_angle_radians = acos( double_abs(eye->current_postion_mm) / eye->length_mm );
		eye->current_angle_radians += (M_PI/2);

	}


    return 0;
}





uint32_t Eye_MoveDistance(EyeParameters_t* eye, double distToMove_mm) {


	// Check that inputs are good
	if((eye->current_postion_mm+distToMove_mm) > (eye->length_mm))
		return -1;

	// Check that inputs are good
	if((eye->current_postion_mm+distToMove_mm) < (-1*eye->length_mm))
		return -1;



	// Save the prev angle
	double prev_angle_radians = eye->current_angle_radians;

	// Set the position 
	eye->current_postion_mm += distToMove_mm;

	// Calculate the corresponding angle
	if(eye->current_postion_mm <= 0) {

		eye->current_angle_radians = acos( double_abs(eye->current_postion_mm) / eye->length_mm );

	} else if(eye->current_postion_mm > 0) {

		eye->current_angle_radians = M_PI - acos( double_abs(eye->current_postion_mm) / eye->length_mm );
	}

	// Calculate the diff between the current angle and prev angle
	double angle_to_move_radians = eye->current_angle_radians - prev_angle_radians;

	//Set the eye direction
	if(angle_to_move_radians < 0) {
		DRV8825_SetDirection(eye->driver, Reverse);
	} else {
		DRV8825_SetDirection(eye->driver, Forward);
	}

	// Calculate the steps required to move that distance
	uint32_t steps = (eye->steps_per_rev * double_abs(angle_to_move_radians)) / (2 * M_PI);

	// Move that distance
	for(uint32_t ii = 0; ii < steps; ii++)
		DRV8825_QuickStep(eye->driver, 2000);

	// Return success status
	return 0;

}

uint32_t Eye_MoveWireDiameters(EyeParameters_t* eye, CoilParameters_t* coil, double multiple) {

	double wire_diam = Coil_getWireDiam_10um(coil) / 10.0;

	return Eye_MoveDistance(eye, wire_diam*multiple);
}




int Eye_FindHome(EyeParameters_t* eye) {

	int ret = -2;
	int timeout = 0;

	DRV8825_SetDirection(eye->driver, Reverse);

    while(HAL_GPIO_ReadPin(eye->LIMIT_SW_Pin_Port, eye->LIMIT_SW_Pin) == 0 && timeout < eye->steps_per_rev) {
     	DRV8825_QuickStep(eye->driver, 2000);
     	timeout++;
    }

    Eye_SetPosition(eye, -1 * eye->length_mm);

    if(timeout < eye->steps_per_rev) {
    	Eye_MoveDistance(eye, eye->length_mm);
		ret = 0;
    }

    else {
	    ret = -1;
	}


	return ret;
}

void Eye_Start(EyeParameters_t* eye) {
	DRV8825_Wake(eye->driver);
	DRV8825_Enable(eye->driver);
	DRV8825_SetDirection(eye->driver, Forward);

}

void Eye_End(EyeParameters_t* eye) {
	DRV8825_Sleep(eye->driver);
	DRV8825_Disable(eye->driver);
}


