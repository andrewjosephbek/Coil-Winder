/*
 * Feild.h
 *
 *  Created on: Sep 14, 2023
 *      Author: andre
 */

#include "CoilParameters.h"
#include "UserInput.h"

#ifndef INC_FIELD_H_
#define INC_FIELD_H_

typedef struct UI_field_info {

	//function to get coil data
	uint8_t title_pos_x;
	uint8_t title_pos_y;
	uint8_t value_title_offset;
	uint8_t fast_press_multiplier;
	uint8_t fixed_point_precision;
	uint8_t blanking_interval;

	char title[10];

	UserInput_t* user_input;

	int (*getFieldValue)(CoilParameters_t*);
	int (*incFieldValue)(CoilParameters_t*, int);

	uint8_t value_pos_x;
	uint8_t value_pos_y;

} UIField_t;


void UIField_Init(UIField_t* field, uint8_t title_pos_x, uint8_t title_pos_y, uint8_t value_title_offset, uint8_t fast_press_multiplier, uint8_t fixed_point_precision, char * title, UserInput_t* user_input, int (*getFieldValue)(CoilParameters_t*), int (*incFieldValue)(CoilParameters_t*, int));

void UIField_UpdateValue(UIField_t* field, CoilParameters_t* coil);

void UIField_Print(UIField_t* field, CoilParameters_t* coil);

void UIField_RePrint(UIField_t* field,CoilParameters_t* coil);

void UIField_PrintTitle(UIField_t* field);

void UIField_SetCursorOnField(UIField_t* field);


#endif /* INC_FEILD_H_ */
