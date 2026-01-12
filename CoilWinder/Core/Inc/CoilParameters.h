/*
 * CoilParameters.h
 *
 *  Created on: Aug 11, 2023
 *      Author: andre
 */

#ifndef INC_COILPARAMETERS_H_
#define INC_COILPARAMETERS_H_

#include "stm32l4xx_hal.h"

/**
 * @brief
 * Stores info about an electrical coil
*/
typedef struct coil_info {
	int wire_diameter_10um; 	// diameter of wire used in the coil in units of 10um
	int coil_diameter_10um;		// coil diameter in units of 10 um
	int coil_width_10um;		// coil width in units in 10 um
	int coil_layers;			// number of layers in the coil

} CoilParameters_t;

/** 
 * @brief
 * Initializes a coil object
 * 
 * @details
 * Fills the variables in the object pointed to by 'coil' with user provided data
 * 
 * @param coil 						A pointer to the button object being operated on
 * @param wire_diameter_10um		diameter of wire used in the coil in units of 10um
 * @param coil_diameter_10um		coil diameter in units of 10 um
 * @param coil_width_10um 			coil width in units in 10 um
 * @param coil_layers				number of layers in the coil
 *
 */
void Coil_Init(CoilParameters_t* coil, int wire_diameter_10um, int coil_diameter_10um, int coil_width_10um, int coil_layers);

/**
 * @brief
 * Access functions
 *
 * @returns
 * CoilParameters_t member values
*/
int Coil_getWireDiam_10um(CoilParameters_t* coil);
int Coil_getCoilDiam_10um(CoilParameters_t* coil);
int Coil_getCoilWidth_10um(CoilParameters_t* coil);
int Coil_getCoilLayers(CoilParameters_t* coil);

/**
 * @brief
 * Sets CoilParameters_t members to the provided value, with protection for negative values
 * 
 * @details
 * Sets CoilParameters_t members to the value specified by new_[MEMBER NAME]
 * If set amount is negative, member is set to 0
 * 
 * @returns
 * If set amount is negative returns -1, otherwise returns 0.
*/
int Coil_setWireDiam_10um(CoilParameters_t* coil, int new_wire_diameter_10um);
int Coil_setCoilDiam_10um(CoilParameters_t* coil, int new_coil_diameter_10um);
int Coil_setCoilWidth_10um(CoilParameters_t* coil, int new_coil_width_10um);
int Coil_setCoilLayers(CoilParameters_t* coil, int coil_layers);

/**
 * @brief
 * Increments CoilParameters_t object members, with protection for negative increments
 * 
 * @details
 * Increments CoilParameters_t members by the amount specified by inc. 
 * If said increment amount would make a member negative, member is set to 0.
 * 
 * @returns
 * If increment amount would make member negative, returns -1, otherwise returns 0.
*/
int Coil_incWireDiam_10um(CoilParameters_t* coil, int inc);
int Coil_incCoilDiam_10um(CoilParameters_t* coil, int inc);
int Coil_incCoilWidth_10um(CoilParameters_t* coil, int inc);
int Coil_incCoilLayers(CoilParameters_t* coil, int inc);



uint32_t Coil_isValid(CoilParameters_t* coil);

#endif /* INC_COILPARAMETERS_H_ */
