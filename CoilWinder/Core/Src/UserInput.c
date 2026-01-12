/*
 * UserInput.c
 *
 *  Created on: Sep 14, 2023
 *      Author: andre
 */
#include "UserInput.h"
#include "Button.h"


void UserInput_Init(UserInput_t* user_input, Button_t * decrement_button, Button_t * increment_button, Button_t * select_button) {

	user_input->decrement_button = decrement_button;
	user_input->increment_button = increment_button;
	user_input->select_button = select_button;

}


void UserInput_Update(UserInput_t* user_input) {

	user_input->decrement_btn_state = 	Button_DetectPress(user_input->decrement_button);
	user_input->increment_btn_state = 	Button_DetectPress(user_input->increment_button);
	user_input->select_btn_state = 		Button_DetectPress(user_input->select_button);

}

enum user_input_types UserInput_Get(UserInput_t* user_input) {

		enum user_input_types input = None;

	    if (user_input->increment_btn_state == Pressed)
	    	input = Increment;

	    else if (user_input->increment_btn_state == Fast_Press)
	    	input = Increment_Fast;

	    else if (user_input->decrement_btn_state == Pressed)
	    	input = Decrement;

	    else if (user_input->decrement_btn_state == Fast_Press)
	    	input = Decrement_Fast;

	    else if (user_input->select_btn_state == Pressed)
	    	input = Select;

	    return input;

}
