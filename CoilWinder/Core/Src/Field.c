/*
 * Feild.c
 *
 *  Created on: Sep 14, 2023
 *      Author: andre
 */
#include "UserInput.h"
#include <Field.h>
#include <string.h>
#include "liquidcrystal_i2c.h"
#include <stdio.h>
#include <CoilWinderUtils.h>


void UIField_Init(UIField_t* field, uint8_t title_pos_x, uint8_t title_pos_y, uint8_t value_title_offset, uint8_t fast_press_multiplier, uint8_t fixed_point_precision, char * title, UserInput_t* user_input, int (*getFieldValue)(CoilParameters_t*), int (*incFieldValue)(CoilParameters_t*, int)) {
	field->title_pos_x = title_pos_x;
	field->title_pos_y = title_pos_y;
	field->value_title_offset = value_title_offset;
	field->fast_press_multiplier = fast_press_multiplier;
	field->fixed_point_precision = fixed_point_precision;

	strcpy(field->title, title);

	field->user_input = user_input;
	field->getFieldValue = getFieldValue;
	field->incFieldValue = incFieldValue;

	field->value_pos_x = title_pos_x + value_title_offset;
	field->value_pos_y = title_pos_y ;

	field->blanking_interval = INT_BLANK_SIZE;
}

void UIField_UpdateValue(UIField_t* field, CoilParameters_t* coil) {


	enum user_input_types current_input = UserInput_Get(field->user_input);


	if(current_input == Increment_Fast) {
		field->incFieldValue(coil, field->fast_press_multiplier);
	} else if (current_input == Decrement_Fast) {
		field->incFieldValue(coil, field->fast_press_multiplier * -1);
	} else if(current_input == Increment){
		field->incFieldValue(coil, 1);
	} else if(current_input == Decrement) {
		field->incFieldValue(coil, -1);

	}

}

void UIField_Print(UIField_t* field,CoilParameters_t* coil) {

    char str[20];
    uint32_t field_value = field->getFieldValue(coil);


    HD44780_SetCursor(field->value_pos_x, field->value_pos_y);

    for(int i = 0; i < INT_BLANK_SIZE; i++)
    	HD44780_PrintStr(" ");

    HD44780_SetCursor(field->value_pos_x, field->value_pos_y);

    sprintf(str, "%d", (int)field_value);

    integerStringToFixedPointString(str, field->fixed_point_precision);
    HD44780_PrintStr(str);

    HD44780_SetCursor(field->value_pos_x, field->value_pos_y);
}

void UIField_RePrint(UIField_t* field,CoilParameters_t* coil) {


	if(!UserInput_Get(field->user_input))
		return;


	UIField_Print(field, coil);
}

void UIField_PrintTitle(UIField_t* field) {
    HD44780_SetCursor(field->title_pos_x, field->title_pos_y);
	HD44780_PrintStr(field->title);
}

void UIField_SetCursorOnField(UIField_t* field) {
    HD44780_SetCursor(field->value_pos_x, field->value_pos_y);
}
