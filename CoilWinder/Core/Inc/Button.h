/*
 * Button.h
 *
 *  Created on: Aug 11, 2023
 *      Author: andre
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "stm32l4xx_hal.h"


enum press_types { Not_Pressed = 0, Pressed = 1, Fast_Press = 2};
enum stage_types { Debounce_Stage = 0, Pressed_Stage = 1, Hold_Stage = 2};

/**
 * @brief
 * Stores info about a button (current state, settings, GPIO access)
*/

typedef struct button_info {
	uint8_t fastPressHoldEnabled;		// When 1, press and hold on button will result in rapid press behavior. When 0, behavior disabled
	uint8_t pressLogicLevel;			// GPIO logic level when the button is in it's pressed state

	GPIO_TypeDef* BUTTON_Pin_Port;		// Button GPIO Port
	uint16_t BUTTON_Pin;				// Button GPIO Pin

	uint8_t pressEvent;					// records in what stage the button is currently in (de-bounce period -> pressed -> fast press)
	uint8_t prevState;					// the logic state of the button in the previous tick
	uint32_t lastPress;					// records the time since last button press

} Button_t;

/** 
 * @brief
 * Initializes a Button_t object
 * 
 * @details
 * Fills the members of the object pointed to by 'button' with user provided data
 * 
 * @param button 					A pointer to the button object being operated on
 * @param BUTTON_Pin_Port			Button GPIO Port
 * @param BUTTON_Pin				Button GPIO Pin
 * @param fastPressHoldEnabled 	When 1, press and hold on button will result in rapid press behavior. When 0, behavior disabled
 * @param pressLogicLevel			GPIO logic level when the button is in it's pressed state
 *
 */
void Button_Init(	Button_t* button,
					GPIO_TypeDef* BUTTON_Pin_Port,
					uint16_t BUTTON_Pin,
					uint8_t fastPressHoldEnabled,
					uint8_t pressLogicLevel);

/** 
 * @brief
 * Detects a button press
 * 
 * @details
 * This function is called repeatedly, to detects a button press in 3 stages:
 * 
 * 1. 	Debounce stage: If a pressed logic level is detected, the function enters the debounce stage and returns 0.
 *   	If after 50ms the button is still pressed, the function advances to the next stage.
 * 2.	Pressed stage: When in this stage, the function will return 1 for a single tick signifying a press, then 
 * 		return 0 until the next stage is reached.
 * 3.	Hold stage: if after 850ms the button has been continually depressed, the function enters the hold stage.
 * 		When in the hold stage, the function returns 2 repeatedly (fast press) until the button is released.
 * 
 * @param button 	A pointer to the button object being operated on
 * 
 * @return
 * When button is pressed, function will return 1 for a single tick, then hold 0.
 * A press is only registered after the 50ms de-bounce period expires
 * If fastPressHoldEnabled == 1, function will repeatedly return 2 when button is held in the pressed state for 850ms
 */
uint8_t Button_DetectPress(Button_t* button);

/**
 * @brief
 * Disables the hold for fast press behavior
 */
void Button_EnableFastPress(Button_t* button);

/**
 * @brief
 * Enables the hold for fast press behavior
 */
void Button_DisableFastPress(Button_t* button);

#endif /* INC_BUTTON_H_ */
