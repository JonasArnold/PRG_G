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
	static bool dirToIsland = false; // Boolean to show the direction of the traffic flow
	static bool dirSwitch = false; // identifies if the direction is currently being switched

	// state machine. 0 = initial, 1 = traffic flow normal, 2 = direction switch ongoing
	static uint8_t state = 0;

	bool carWaiting = false;

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
			carWaiting = true;
			carsOnIsland--; // TODO not sure
			il_out = false; // acknowledge sensor
		}
	} else { /* direction to mainland */
		/* update counters, acknowledge sensors */
		if (il_out) {
			carsOnBridge++;
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
			carWaiting = true;
			ml_out = false; // acknowledge sensor
		}
	}

	/* State Machine */
	switch (state) {
	case 0: // initial state
		dirToIsland = false;  // direction to island, set traffic lights
		ml = red;
		il = green;

		state = 1;    // state to "normal traffic flow"
		break;

	case 1: // traffic flow normal
		if (dirToIsland) {
			/* max number of cars reached */
			if (carsOnBridge + carsOnIsland >= max_cars) {
				state = 2;    // initiate direction switch
				ml = red;     // stop traffic from mainland
			}

			/* car is waiting at island */
			if (carWaiting) {
				state = 2;    // initiate direction switch
				ml = red;     // stop traffic from mainland
			}
		}
		else {  // direction: mainland
			/* car is waiting at mainland and max cars in island not reached*/
			if (carWaiting && (carsOnBridge + carsOnIsland < max_cars)) {
				state = 2;    // initiate direction switch
				il = red;         // stop traffic from mainland
			}
		}

		break;

	case 2: // direction switch ongoing
		if (carsOnBridge == 0) { // perform direction switch only if no cars on bridge
			dirToIsland = dirToIsland ? false : true; // change direction variable
			// switch traffic lights
			if (dirToIsland) {
				ml = green;
			} else {
				il = green;
			}
			state = 1;  // state to "normal traffic flow"
		}

		break;
	}

}

