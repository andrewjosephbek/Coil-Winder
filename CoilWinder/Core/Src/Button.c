/*
 * Button.c
 *
 *  Created on: Aug 11, 2023
 *      Author: andre
 */

#include "Button.h"
#include "stm32l4xx_hal.h"

void Button_Init(	Button_t* button,
					GPIO_TypeDef* BUTTON_Pin_Port,
					uint16_t BUTTON_Pin,
					uint8_t fastPressHoldEnabled,
					uint8_t pressLogicLevel) {

	button->BUTTON_Pin_Port = BUTTON_Pin_Port;
	button->BUTTON_Pin = BUTTON_Pin;
	button->fastPressHoldEnabled = fastPressHoldEnabled;
	button->pressLogicLevel = pressLogicLevel;
	button->pressEvent = 0;
	button->prevState = 0;
	button->lastPress = 0;

}

uint8_t Button_DetectPress(Button_t* button) {


		uint8_t button_status = Not_Pressed;
		uint8_t currentState = HAL_GPIO_ReadPin(button->BUTTON_Pin_Port, button->BUTTON_Pin);

	    //if a rising edge is detected, begin a press event
	    if (currentState == button->pressLogicLevel && button->prevState == !(button->pressLogicLevel) && button->pressEvent == Debounce_Stage) {

	        button->lastPress = HAL_GetTick();
	        button->pressEvent = Pressed_Stage;
	        button->prevState = currentState;
	    }
	    //if a press event is active, and the de-bounce period has expired,
	    //set the button status to the current state of the button
	    else if (button->pressEvent == Pressed_Stage && ((HAL_GetTick() - button->lastPress) > 20)) {

	    	button->pressEvent = Hold_Stage;

	    	if(currentState == button->pressLogicLevel)
	    		button_status = Pressed;

	    }

	    //if a fast press event is queued, but the button has been released, cancel the event
	    else if (button->pressEvent == Hold_Stage && currentState == !(button->pressLogicLevel)) {

	    	button->pressEvent = Debounce_Stage;
	        button_status = Not_Pressed;
	    }
	    //if a fast press event is queued and the button is pressed, start the event
	    else if (button->fastPressHoldEnabled && button->pressEvent == Hold_Stage && currentState == button->pressLogicLevel && ((HAL_GetTick() - button->lastPress) > 850)) {

	        button_status = Fast_Press;
	    }

	    button->prevState = currentState;

	    return button_status;
}

void Button_EnablefastPress(Button_t* button) {
	button->fastPressHoldEnabled = 1;
}

void Button_DisablefastPress(Button_t* button) {
	button->fastPressHoldEnabled = 0;
}
