/*
 * UserInput.h
 *
 *  Created on: Sep 14, 2023
 *      Author: andre
 */

#include "Button.h"

#ifndef USER_INPUT_H_
#define USER_INPUT_H_

enum user_input_types { None = 0, Increment = 1, Decrement = -1, Increment_Fast = 2, Decrement_Fast = -2, Select = 3};

typedef struct user_input_info {
	Button_t * decrement_button;
	Button_t * increment_button;
	Button_t * select_button;

	uint8_t decrement_btn_state;
	uint8_t increment_btn_state;
	uint8_t select_btn_state;

} UserInput_t;


void UserInput_Init(UserInput_t* user_input, Button_t * decrement_button, Button_t * increment_button, Button_t * select_button);

void UserInput_Update(UserInput_t* user_input);

enum user_input_types UserInput_Get(UserInput_t* user_input);

#endif /* INC_FEILD_H_ */
