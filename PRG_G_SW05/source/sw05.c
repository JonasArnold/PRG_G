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

/* maximal number of cycles the direction stays the same */
const uint8_t max_cycle_per_dir = 20;

/* sensors ml (mainland) il (island) in and out */
bool ml_out, il_out, ml_in, il_in = false;

/* traffic light mainland, island */
color_t ml, il = red;

void controller(void) {

	/* this function will be called (i.e. activated),
	 * each time a sensor changes its state. set
	 * traffic lights at mainland (ml) and island (il)
	 * such, that all requirements are met. sensors
	 * are set to 'true' if a car is LEAVING the corresponding
	 * area, set the signal back to 'false' to acknowledge
	 * the processing. */

	/*                                                   ____
	 *     ___________________                          |O__0|   ___________________
	 *    |                   | __________________________ml___ |                   |
	 *    |                   | il_in                           | ml_out            |
	 *    |  Island           |                                 |          Mainland |
	 *    |            il_out | _________________________ml_in_ |                   |
	 *    |___________________|   ____                          |___________________|
	 *                           |0__O|
	 *                             il
	 */

	static uint8_t carsOnBridge = 0; // Counter to count amount of cars on bridge
	static uint8_t carsOnIsland = 0; // Counter to count amount of cars on island
	static uint16_t thisDirCount = 0; // Count how many cycles the traffic flows in this direction
	static bool dirToIsland = false; // Boolean to show the direction of the traffic flow

	// state machine. 0 = initial, 1 = traffic flow normal, 2 = direction switch ongoing
	static uint8_t state = 0;

	/* Gather sensor information */
	if (dirToIsland) {
		/* update counters, acknowledge sensors */
		if (ml_out) {
			carsOnBridge++;
			ml_out = false;  // acknowledge sensor
		}
		if (il_in) {
			carsOnBridge--;
			carsOnIsland++;
			il_in = false;  // acknowledge sensor
		}
		if (ml_in) {
			printf("ERROR: Car entered mainland but traffic flows other direction.");
			ml_in = false;  // acknowledge sensor
		}
		if (il_out) {
			printf("ERROR: Car left island but traffic flows other direction.");
			carsOnBridge++;
			carsOnIsland--;
			il_out = false; // acknowledge sensor
		}
	} else { /* direction to mainland */
		/* update counters, acknowledge sensors */
		if (il_out) {
			carsOnBridge++;
			carsOnIsland--;
			il_out = false; // acknowledge sensor
		}
		if (ml_in) {
			carsOnBridge--;
			ml_in = false;  // acknowledge sensor
		}
		if (il_in) {
			printf("ERROR: Car entered island but traffic flows other direction.");
			il_in = false;  // acknowledge sensor
		}
		if (ml_out) {
			printf("ERROR: Car left mainland but traffic flows other direction.");
			carsOnBridge++;
			ml_out = false; // acknowledge sensor
		}
	}
	thisDirCount++;

	/* State Machine */
	switch (state) {
	case 0: // initial state
		dirToIsland = false;  // direction to island, set traffic lights
		ml = red;
		il = green;

		state = 1;    // state to "normal traffic flow"
		break;

	case 1: // traffic flow normal

		/* max number of cars on island reached */
		if (dirToIsland && (carsOnBridge + carsOnIsland >= max_cars)) {
			state = 2;    // initiate direction switch
			ml = red;     // stop traffic from mainland
		}

		/* switch direction if too many cycles in one direction */
		if (thisDirCount > max_cycle_per_dir) {

			// check number of cars first
			if (carsOnBridge + carsOnIsland < max_cars) {
				// switch direction
				il = red;
				ml = red;
				state = 2;
			} else { // max number of cars on island => do not switch direction
				thisDirCount = 0; // reset counter to not run into memory issues
			}
		}
		break;

	case 2:
	// direction switch ongoing
	if (carsOnBridge == 0) { // perform direction switch only if no cars on bridge
		dirToIsland = dirToIsland ? false : true; // change direction variable
		// switch traffic lights
		if (dirToIsland) {
			ml = green;
		} else {
			il = green;
		}
		thisDirCount = 0;
		state = 1;  // state to "normal traffic flow"
	}

	break;
}

}

