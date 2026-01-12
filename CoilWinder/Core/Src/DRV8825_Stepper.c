/*
 * DRV8825_Stepper.c
 *
 *  Created on: Aug 11, 2023
 *      Author: andre
 */

#include "DRV8825_Stepper.h"
#include "stm32l4xx_hal.h"
#include "CoilWinderUtils.h"

// Private Helper Functions

void DRV8825_setMicroStepDirect(DRV8825_Stepper_t* driver, uint8_t M0, uint8_t M1, uint8_t M2) {
	HAL_GPIO_WritePin(driver->MICROSTEP_Pin_M0_Port, driver->MICROSTEP_Pin_M0, M0);
	HAL_GPIO_WritePin(driver->MICROSTEP_Pin_M1_Port, driver->MICROSTEP_Pin_M1, M1);
	HAL_GPIO_WritePin(driver->MICROSTEP_Pin_M2_Port, driver->MICROSTEP_Pin_M2, M2);
}

uint8_t DRV8825_microsteppingPinsNotConfigured(DRV8825_Stepper_t* driver) {
	if(	driver->MICROSTEP_Pin_M0_Port == NULL || driver->MICROSTEP_Pin_M0 == -1 ||
		driver->MICROSTEP_Pin_M1_Port == NULL || driver->MICROSTEP_Pin_M1 == -1 ||
		driver->MICROSTEP_Pin_M2_Port == NULL || driver->MICROSTEP_Pin_M2 == -1)
			return 1;

	return 0;
}


// Public Driver Functions

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
					uint8_t microstep_config  ) {


	if(STEP_Pin_Port == NULL || STEP_Pin == -1)
		return -1;

	driver->STEP_Pin_Port = STEP_Pin_Port;
	driver->STEP_Pin = STEP_Pin;

	driver->DIR_Pin_Port = DIR_Pin_Port;
	driver->DIR_Pin = DIR_Pin;

	driver->SLEEP_Pin_Port = SLEEP_Pin_Port;
	driver->SLEEP_Pin = SLEEP_Pin;

	driver->RESET_Pin_Port = RESET_Pin_Port;
	driver->RESET_Pin = RESET_Pin;

	driver->ENABLE_Pin_Port = ENABLE_Pin_Port;
	driver->ENABLE_Pin = ENABLE_Pin;

	driver->MICROSTEP_Pin_M0_Port = MICROSTEP_Pin_M0_Port;
	driver->MICROSTEP_Pin_M0 = MICROSTEP_Pin_M0;

	driver->MICROSTEP_Pin_M1_Port = MICROSTEP_Pin_M1_Port;
	driver->MICROSTEP_Pin_M1 = MICROSTEP_Pin_M1;

	driver->MICROSTEP_Pin_M2_Port = MICROSTEP_Pin_M2_Port;
	driver->MICROSTEP_Pin_M2 = MICROSTEP_Pin_M2;

	DRV8825_SetMicrostepLevel(driver, microstep_config);
	DRV8825_Enable(driver);
	DRV8825_Sleep(driver);
	DRV8825_SetDirection(driver, 0);

	HAL_GPIO_WritePin(driver->DIR_Pin_Port, driver->DIR_Pin, 1);

	return 0;

}


int DRV8825_GetDirection(DRV8825_Stepper_t* driver) {
	if(driver->DIR_Pin_Port == NULL || driver->DIR_Pin == -1)
		return -1;

	return HAL_GPIO_ReadPin(driver->DIR_Pin_Port, driver->DIR_Pin);
}

int DRV8825_SetDirection(DRV8825_Stepper_t* driver, uint8_t dir) {
	if(driver->DIR_Pin_Port == NULL || driver->DIR_Pin == -1)
		return -1;

	dir = !!dir;

	HAL_GPIO_WritePin(driver->DIR_Pin_Port, driver->DIR_Pin, dir);

	return 0;
}

int DRV8825_ToggleDirection(DRV8825_Stepper_t* driver) {
	if(driver->DIR_Pin_Port == NULL || driver->DIR_Pin == -1)
		return -1;

	uint8_t dir = HAL_GPIO_ReadPin(driver->DIR_Pin_Port, driver->DIR_Pin);

	HAL_GPIO_WritePin(driver->DIR_Pin_Port, driver->DIR_Pin, !dir);

	return 0;
}

void DRV8825_Step(DRV8825_Stepper_t* driver, uint32_t delay_millis) {

	HAL_GPIO_WritePin(driver->STEP_Pin_Port, driver->STEP_Pin, 0);
	HAL_GPIO_WritePin(driver->STEP_Pin_Port, driver->STEP_Pin, 1);
	HAL_Delay(delay_millis);

}
void DRV8825_QuickStep(DRV8825_Stepper_t* driver, uint32_t iters)
{
	HAL_GPIO_WritePin(driver->STEP_Pin_Port, driver->STEP_Pin, 0);
	delay_iterations(iters);
	HAL_GPIO_WritePin(driver->STEP_Pin_Port, driver->STEP_Pin, 1);
	delay_iterations(iters);

}
int DRV8825_Wake(DRV8825_Stepper_t* driver) {
	if(driver->SLEEP_Pin_Port == NULL || driver->SLEEP_Pin == -1)
		return -1;

	HAL_GPIO_WritePin(driver->SLEEP_Pin_Port, driver->SLEEP_Pin, 1);

	return 0;
}

int DRV8825_Sleep(DRV8825_Stepper_t* driver) {
	if(driver->SLEEP_Pin_Port == NULL || driver->SLEEP_Pin == -1)
		return -1;
	
	HAL_GPIO_WritePin(driver->SLEEP_Pin_Port, driver->SLEEP_Pin, 0);
	
	return 0;
}

int DRV8825_Enable(DRV8825_Stepper_t* driver) {
	if(driver->ENABLE_Pin_Port == NULL || driver->ENABLE_Pin == -1)
		return -1;
	
	HAL_GPIO_WritePin(driver->ENABLE_Pin_Port, driver->ENABLE_Pin, 0);
	
	return 0;
}


int DRV8825_Disable(DRV8825_Stepper_t* driver) {
	if(driver->ENABLE_Pin_Port == NULL || driver->ENABLE_Pin == -1)
		return -1;
	
	HAL_GPIO_WritePin(driver->ENABLE_Pin_Port, driver->ENABLE_Pin, 1);
	
	return 0;
}


int DRV8825_Reset(DRV8825_Stepper_t* driver) {
	if(driver->RESET_Pin_Port == NULL || driver->RESET_Pin == -1)
		return -1;

	HAL_GPIO_WritePin(driver->RESET_Pin_Port, driver->RESET_Pin, 0);
	HAL_Delay(100);
	HAL_GPIO_WritePin(driver->RESET_Pin_Port, driver->RESET_Pin, 1);

	return 0;
}



int DRV8825_SetMicrostepLevel(DRV8825_Stepper_t* driver, uint8_t microstep_level) {

	if(DRV8825_microsteppingPinsNotConfigured(driver))
		return -1;

	uint8_t status;

	switch(microstep_level) {

	case 1:
		DRV8825_setMicroStepDirect(driver, 0, 0, 0);
		status = 0;
		break;
	case 2:
		DRV8825_setMicroStepDirect(driver, 1, 0, 0);
		status = 0;
		break;
	case 4:
		DRV8825_setMicroStepDirect(driver, 0, 1, 0);
		status = 0;
		break;
	case 8:
		DRV8825_setMicroStepDirect(driver, 1, 1, 0);
		status = 0;
		break;
	case 16:
		DRV8825_setMicroStepDirect(driver, 0, 0, 1);
		status = 0;
		break;
	case 32:
		DRV8825_setMicroStepDirect(driver, 1, 1, 1);
		status = 0;
		break;
	default:
		status = 1;
	}

	if(status == 0)
		driver->microstep_config = microstep_level;

	return status;
}

int DRV8825_GetMicrostepLevel(DRV8825_Stepper_t* driver) {
	if(DRV8825_microsteppingPinsNotConfigured(driver))
		return -1;

	return driver->microstep_config;
}
