/*
 * DRV8825_Stepper.h
 *
 *  Created on: Aug 11, 2023
 *      Author: andre
 */

#ifndef INC_DRV8825_STEPPER_H_
#define INC_DRV8825_STEPPER_H_

#define FORWARD  1			//Forward logic level on the DRV8825 Step pin
#define REVERSE  0			//Reverse logic level on the DRV8825 Step pin

enum direction { Forward = 1, Reverse = 0};

#include "stm32l4xx_hal.h"

/**
 * @brief
 * Stores info about a stepper_driver (current state, settings, GPIO access)
*/

typedef struct stepper_info {
	uint8_t microstep_config;				// the current micro-step level the driver is set at (microstep_config == [1: no micro-stepping, 2: 1/2 steps, 4: 1/4 steps ... 32: 1/32 steps])

	GPIO_TypeDef* STEP_Pin_Port;			// Step input GPIO pin and port
	uint16_t STEP_Pin;						// a rising edge on this pin will advance the motor 1 step

	GPIO_TypeDef* DIR_Pin_Port;				// Direction input GPIO pin and port
	uint16_t DIR_Pin;						// toggling this pin will toggle the direction fo the motor

	GPIO_TypeDef* SLEEP_Pin_Port;			// Sleep input GPIO pin and port
	uint16_t SLEEP_Pin;						// a HIGH signal on this pin will wake the driver, a low signal will put the driver into low current mode

	GPIO_TypeDef* RESET_Pin_Port;			// Reset input GPIO pin and port
	uint16_t RESET_Pin;						// a LOW signal on this line will reset the driver (i.e. set the micro-step table back to position 0);

	GPIO_TypeDef* ENABLE_Pin_Port;			// Enable input GPIO pin and port
	uint16_t ENABLE_Pin;					// a Low signal will disable the driver

	GPIO_TypeDef* MICROSTEP_Pin_M0_Port;		// Micro-step inputs A-C GPIO pin(s) and port(s)
	uint16_t MICROSTEP_Pin_M0;				// this 3 bit signal determines the micro-step level of the driver

	GPIO_TypeDef* MICROSTEP_Pin_M1_Port;		// ...
	uint16_t MICROSTEP_Pin_M1;

	GPIO_TypeDef* MICROSTEP_Pin_M2_Port;		// ...
	uint16_t MICROSTEP_Pin_M2;

} DRV8825_Stepper_t;


/**
 * @brief
 * Initializes a stepper driver object
 *
 * @details
 * Fills the members of the object pointed to by 'driver' with user provided data. 
 * Enables the driver, puts it in sleep mode, sets the driver direction pin to LOW, 
 * and sets the micro-step pin array to the micro-step resolution specified by microstep_config.
 * 
 * @param driver									a pointer to the DRV8825_Stepper_t object being operated on
 * @param STEP_Pin_Port, STEP_Pin					Step input GPIO pin and port
 * @param DIR_Pin_Port, DIR_Pin						Direction input GPIO pin and port
 * @param SLEEP_Pin_Port, SLEEP_Pin					Sleep input GPIO pin and port
 * @param RESET_Pin_Port, RESET_Pin					Reset input GPIO pin and port
 * @param ENABLE_Pin_Port, ENABLE_Pin				Enable input GPIO pin and port
 * @param MICROSTEP_Pin_A_Port, MICROSTEP_Pin_A 	Micro-step inputs A-C GPIO pin(s) and port(s)
 * @param MICROSTEP_Pin_B_Port, MICROSTEP_Pin_B		...
 * @param MICROSTEP_Pin_C_Port, MICROSTEP_Pin_C		...
 * @param microstep_config							// the current micro-step resolution the driver is set at (microstep_config == [1: no micro-stepping, 2: 1/2 steps, 4: 1/4 steps ... 32: 1/32 steps])
 * 
 * @returns 
 * returns 0 if initialization runs successfully
 * returns -1 if no step pin and port are specified (initialization unsuccessful)
 * 
 */
int DRV8825_Init(	DRV8825_Stepper_t* driver,
					GPIO_TypeDef* STEP_Pin_Port,
					uint16_t STEP_Pin,
					GPIO_TypeDef* DIR_Pin_Port,
					uint16_t DIR_Pin,
					GPIO_TypeDef* SLEEP_Pin_Port,
					uint16_t SLEEP_Pin,
					GPIO_TypeDef* RESET_Pin_Port,
					uint16_t RESET_Pin,
					GPIO_TypeDef* ENABLE_Pin_Port,
					uint16_t ENABLE_Pin,
					GPIO_TypeDef* MICROSTEP_Pin_M0_Port,
					uint16_t MICROSTEP_Pin_M0,
					GPIO_TypeDef* MICROSTEP_Pin_M1_Port,
					uint16_t MICROSTEP_Pin_M1,
					GPIO_TypeDef* MICROSTEP_Pin_M2_Port,
					uint16_t MICROSTEP_Pin_M2, 
					uint8_t microstep_config);



/**
 * @brief
 * Gets the state of the direction pin
 * 
 * @returns
 * returns 1 if pin is HIGH
 * returns 0 if pin is LOW 
 * returns -1 if no direction pin is configured
*/
int DRV8825_GetDirection(DRV8825_Stepper_t* driver);




/**
 * @brief
 * Sets the state of the direction pin
 * 
 * @param dir the state that the direction GPIO pin should be set to
 * 
 * @returns
 * returns 0 if the operation was successful
 * returns -1 if no direction pin is configured
*/
int DRV8825_SetDirection(DRV8825_Stepper_t* driver, uint8_t dir);




/**
 * @brief
 * Toggles the state of the direction pin
 * 
 * @returns
 * returns 0 if the operation was successful
 * returns -1 if no direction pin is configured
*/
int DRV8825_ToggleDirection(DRV8825_Stepper_t* driver);




/**
 * @brief
 * Advances the stepper motor 1 step, followed by a user provided delay 
 * 
 * @param delay_millis the time delay after the motor takes a step
 * 
 * @warning
 * DRV8825_Init(driver) must return 0 at least once before this function is called.
 * 
*/
void DRV8825_Step(DRV8825_Stepper_t* driver, uint32_t delay_millis);




/**
 * @brief
 * Advances the stepper motor 1 step, with a predetermined sub 1ms delay following the step
 *  
 * @warning
 * DRV8825_Init(driver) must return 0 at least once before this function is called.
 * 
*/
void DRV8825_QuickStep(DRV8825_Stepper_t* driver, uint32_t iters);



/**
 * @brief
 * Sets the SLEEP_Pin HIGH, waking the driver
 * 
 * @returns
 * returns 0 if operation was successful
 * returns -1 if no SLEEP_PIN configured
*/
int DRV8825_Wake(DRV8825_Stepper_t* driver);




/**
 * @brief
 * Sets the SLEEP_Pin LOW, sleeping the driver
 * 
 * @returns
 * returns 0 if operation was successful 
 * returns -1 if no SLEEP_PIN configured
*/
int DRV8825_Sleep(DRV8825_Stepper_t* driver);




/**
 * @brief
 * Sets the ENABLE_Pin LOW, enabling the driver
 * 
 * @returns
 * returns 0 if operation was successful,
 * returns -1 if no ENABLE_PIN configured
*/
int DRV8825_Enable(DRV8825_Stepper_t* driver);




/**
 * @brief
 * Sets the ENABLE_Pin HIGH, disabling the driver
 * 
 * @returns
 * returns 0 if operation was successful
 * returns -1 if no ENABLE_PIN configured
*/
int DRV8825_Disable(DRV8825_Stepper_t* driver);




/**
 * @brief
 * Sets the RESET_PIN high for 100ms, reseting the driver
 * 
 * @returns
 * returns 0 if operation was successful
 * returns -1 if no RESET_PIN configured
*/
int DRV8825_Reset(DRV8825_Stepper_t* driver);




/**
 * @brief
 * Sets the drivers microstep resolution
 * 
 * @details
 * Set's the microstep configuration pins to the corresponding microstep resolution, given by microstep_level. 
 * Contains protection against bad inputs.
 * 
 * @param microstep_level 	The micro-step resolution to send to the driver. The reciprocal of the microstep_level 
 * 							paramater is the fraction of a full step that the motor will take given a single step command.
 * 							Example: microstep_config == [1: no micro-stepping, 2: 1/2 steps, 4: 1/4 steps ... 32: 1/32 steps]
 * 
 * @returns 
 * returns 1 if invalid microstep_level provided. 
 * returns -1 if micro-stepping isn't configured. 
 * returns 0 if microstep configuration pins are successfully set.
*/							
int DRV8825_SetMicrostepLevel(DRV8825_Stepper_t* driver, uint8_t microstep_level);



/**
 * @brief
 * Gets the drivers microstep resolution
 * 
 * @returns 
 * returns microstep_level, as defined in the DRV8825_Stepper_t typedef
*/
int DRV8825_GetMicrostepLevel(DRV8825_Stepper_t* driver);


#endif /* INC_DRV8825_STEPPER_H_ */

