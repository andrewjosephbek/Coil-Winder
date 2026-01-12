/*
 * EyeParameters.h
 *
 *  Created on: Aug 14, 2023
 *      Author: andre
 */

#ifndef SRC_EYEPARAMETERS_H_
#define SRC_EYEPARAMETERS_H_

#include "stm32l4xx_hal.h"
#include "DRV8825_Stepper.h"
#include "CoilParameters.h"


/**
 * @brief
 * Stores info about an "eye" (the arm attached to the worm wheel assembly on the coil-winder)
 * 
 * @details
 * The 'length' of the eye is defined as the distance from the axis of the stepper motor shaft to the farthest point on the root of the v roller
 *	
 * The eye uses a linear coordinate system to describe it's position:
 * 
 * 		- When the eye is parallel and to the left of the top surface of the eye stepper:
 * 				- current_postion_mm is -[length of the eye]
 * 				- current_angle_radians is 0
 *
 * 		- When the eye is parallel and to the right of the top surface of the eye stepper
 * 				- current_postion_mm is [length of the eye]
 * 				- current_angle_radians is M_PI
*/
typedef struct eye_info {
	DRV8825_Stepper_t* driver;			// Stepper driver associated with this eye

	double current_angle_radians;		// Current angle of the eye in radians

	double current_postion_mm;			// Current position of the eye in the coordinate system described above

	double length_mm;					// Length of the eye as described above
	uint32_t steps_per_rev;				// Number of rising edges on the DRV8825 step line required to complete a full 360 degree rotation of the eye

	GPIO_TypeDef* LIMIT_SW_Pin_Port;	// Homing limit-switch pin and port
	uint16_t LIMIT_SW_Pin;

} EyeParameters_t;

/**
 * @brief
 * Initializes an EyeParameters_t object
 * 
 * 
 * @param length_mm 			Distance from the axis of the stepper motor shaft to the farthest point on the root of the v roller 
 * @param current_postion_mm 	Current position of the eye as described in the eye_info typedef
 * 								When the eye is parallel and to the left of the stepper, it's current_postion is 0. 
 * 								When the eye is parallel and to the right of the stepper, it's current_postion is 2*length_mm.
 * @param steps_per_rev			Number of rising edges on the step line required to complete a full 360 degree rotation of the eye 
 * 
 * @note 
 * current_angle_radians is calculated automatically
 * 
*/
int Eye_Init(EyeParameters_t* eye, DRV8825_Stepper_t* driver, double length_mm, double current_postion_mm, uint32_t steps_per_rev, GPIO_TypeDef* LIMIT_SW_Pin_Port, uint16_t LIMIT_SW_Pin);

/**
 * @brief
 * Sets the eye's position in the coordinate system described in the EyeParameters_t typedef
 * 
 * @details
 * The eye's position is set directly through a simple assignment operation. The angle of the eye is then calculated automatically.
 * 
 * @param current_postion_mm New current position of the eye as described in the eye_info typedef.
 * 
 * @returns
 * returns 0 if position is successfully set
 * returns -1 if current_postion_mm exceeds (2*length_mm)
*/
int Eye_SetPosition(EyeParameters_t* eye, double current_postion_mm);


/**
 * @brief
 * Moves the eye a predetermined distance
 *
 * @param distToMove_mm the distance the eye should move in mm
 * @param dir the direction the eye should move (forward = 1, reverse = 0)
 *
 * returns 0 if the movement was executed
 * returns -1 if current_postion_mm exceeds the bounds of the eye's range
 */
uint32_t Eye_MoveDistance(EyeParameters_t* eye, double distToMove_mm);


uint32_t Eye_MoveWireDiameters(EyeParameters_t* eye, CoilParameters_t* coil, double multiple);


/**
 * @brief
 * Finds the home position of the eye using a limit switch
 *
 * @returns
 * returns 0 if the eye finds its home position.
 * returns -1 if the eye completes a full rotation and exceeds it's time-out.
 */
int Eye_FindHome(EyeParameters_t* eye);

/**
 * @brief
 * Wakes and enables the eye motor, sets its direction to forward.
 */
void Eye_Start(EyeParameters_t* eye);

/**
 * @brief
 * Sleeps and disables the eye motor
 */
void Eye_End(EyeParameters_t* eye);




#endif /* SRC_EYEPARAMETERS_H_ */



