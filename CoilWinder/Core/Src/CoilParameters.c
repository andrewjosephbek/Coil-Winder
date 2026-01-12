/*
 * CoilParameters.c
 *
 *  Created on: Aug 11, 2023
 *      Author: andre
 */


#include "CoilParameters.h"


void Coil_Init(CoilParameters_t* coil, int wire_diameter_10um, int coil_diameter_10um, int coil_width_10um, int coil_layers) {
	coil->wire_diameter_10um = wire_diameter_10um;
	coil->coil_diameter_10um = coil_diameter_10um;
	coil->coil_width_10um = coil_width_10um;
	coil->coil_layers = coil_layers;
}


//get commands


int Coil_getWireDiam_10um(CoilParameters_t* coil) {
	return coil->wire_diameter_10um;
}
int Coil_getCoilDiam_10um(CoilParameters_t* coil) {
	return coil->coil_diameter_10um;
}
int Coil_getCoilWidth_10um(CoilParameters_t* coil) {
	return coil->coil_width_10um;
}
int Coil_getCoilLayers(CoilParameters_t* coil) {
	return coil->coil_layers;
}



//set commands


int Coil_setWireDiam_10um(CoilParameters_t* coil, int new_wire_diameter_10um) {
	if(new_wire_diameter_10um < 0) {
		coil->wire_diameter_10um = 0;
		return -1;
	} else {
		coil->wire_diameter_10um = new_wire_diameter_10um;
		return 0;
	}
}
int Coil_setCoilDiam_10um(CoilParameters_t* coil, int new_coil_diameter_10um) {
	if(new_coil_diameter_10um < 0) {
		coil->coil_diameter_10um = 0;
		return -1;
	} else {
		coil->coil_diameter_10um = new_coil_diameter_10um;
		return 0;
	}
}
int Coil_setCoilWidth_10um(CoilParameters_t* coil, int new_coil_width_10um) {
	if(new_coil_width_10um < 0) {
		coil->coil_width_10um = 0;
		return -1;
	} else {
		coil->coil_width_10um = new_coil_width_10um;
		return 0;
	}
}
int Coil_setCoilLayers(CoilParameters_t* coil, int new_coil_layers) {
	if(new_coil_layers < 0) {
		coil->coil_layers = 0;
		return -1;
	} else {
		coil->coil_layers = new_coil_layers;
		return 0;
	}
}





//increment functions

int Coil_incWireDiam_10um(CoilParameters_t* coil, int increment) {

		coil->wire_diameter_10um += increment;

		if(coil->wire_diameter_10um < 0) {
			coil->wire_diameter_10um = 0;
			return -1;
		}

		return 0;

}
int Coil_incCoilDiam_10um(CoilParameters_t* coil, int increment) {

	coil->coil_diameter_10um += increment;

		if(coil->coil_diameter_10um < 0) {
			coil->coil_diameter_10um = 0;
			return -1;
		}

		return 0;

}
int Coil_incCoilWidth_10um(CoilParameters_t* coil, int increment) {
	coil->coil_width_10um += increment;

		if(coil->coil_width_10um < 0) {
			coil->coil_width_10um = 0;
			return -1;
		}

		return 0;
}
int Coil_incCoilLayers(CoilParameters_t* coil, int increment) {
	coil->coil_layers += increment;

		if(coil->coil_layers < 0) {
			coil->coil_layers = 0;
			return -1;
		}

		return 0;
}

uint32_t Coil_isValid(CoilParameters_t* coil) {


	return 	Coil_getWireDiam_10um(coil) &&
			Coil_getCoilDiam_10um(coil) &&
			Coil_getCoilWidth_10um(coil) &&
			Coil_getCoilLayers(coil);

}


