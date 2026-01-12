/*
 * utils.c
 *
 *  Created on: Aug 11, 2023
 *      Author: andre
 */
#include <string.h>
#include "stm32l4xx_hal.h"



int str_insertChar(char * str, int pos, char ch) {
	int len = strlen(str);
    if (pos >= strlen(str)) return -1;

    for (int i = len; i > pos; i--)
        str[i] = str[i - 1];

    str[pos] = ch;
    str[len+1] = '\0';

    return 0;
}


int integerStringToFixedPointString(char * str, int precision) {
	if(precision <= 0)
		return -1;

    int init_len = strlen(str);

    if (init_len <= precision)
        for (int i = init_len; i <= precision; i++)
        	str_insertChar(str, 0, '0');

    str_insertChar(str, strlen(str) - precision, '.');
    return 0;
}

double double_abs(double num) {
	if(num < 0)
		return num*-1;

	return num;
}

void delay_iterations(uint32_t iterations) {

	for(long i = 0; i < iterations; i++) {
	    __asm__ (
	    		"nop;"

	    );
	}
}

uint32_t us_to_iters(uint32_t microseconds) {
	double iters = 7.27*(microseconds) - 9.09;

	return iters;
}



