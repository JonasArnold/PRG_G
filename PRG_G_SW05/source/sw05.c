/**
 * @file    sw05.c
 * @brief   Solution to homework SW05.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "simulator.h"

/* maximal number of cars on bridge and island together -- do not change this */
const uint8_t max_cars = 10;

/* sensors ml (mainland) il (island) in and out */
bool ml_out, il_out, ml_in, il_in = false;

/* traffic light mainland, island */
color_t ml, il = red;


void controller(void) {

	/* your code here */
	/* ============== */

	/* this function will be called (i.e. activated),
	 * each time a sensor changes its state. set
	 * traffic lights at mainland (ml) and island (il)
	 * such, that all requirements are met. sensors
	 * are set to 'true' if a car is LEAVING the corresponding
	 * area, set the signal back to 'false' to acknowledge
	 * the processing. */


	/* example */

	static bool out = true;	/* 'static' to keep the value of the variable */

	if (out) {			/* set direction */
		ml = green;		/* 		set traffic light on mainland to green */
		il = red;		/*		avoid crossing traffic */
	} else {
		ml = red;
		il = red;
	}

	if (ml_out) { 		/* car left traffic sign outwards */
		ml_out = false;	/* 		acknowledge sensor */
		out = false;	/* 		stop */
	}

	if (il_in) {		/* car arrived at island */
		il_in = false;	/* 		acknowledge sensor */
		out = true;		/*		allow next to enter */
	}

}

