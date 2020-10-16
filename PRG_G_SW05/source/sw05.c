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

	bool carWaiting = false;

	/* ------- DIRECTION TO ISLAND ------- */
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

		/* max number of cars reached and no direction switch ongoing */
		if(carsOnBridge + carsOnIsland >= max_cars && !dirSwitch) {
			dirSwitch = true; // initiate direction switch
			ml = red;         // stop traffic from mainland
		}

		/* car is waiting at island and no direction switch ongoing  */
		if(carWaiting && !dirSwitch){
			dirSwitch = true; // initiate direction switch
			ml = red;         // stop traffic from mainland
		}
	}

	/* ------- DIRECTION TO MAINLAND ------- */
	else {
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

		/* car is waiting at mainland and no direction switch ongoing  */
		if(carWaiting && !dirSwitch){
			dirSwitch = true; // initiate direction switch
			il = red;         // stop traffic from mainland
		}
	}

	/* Direction switch ongoing ? */
	if (dirSwitch) {
		if (carsOnBridge == 0) { // no more cars on bridge
			// perform direction switch now
			dirToIsland = dirToIsland ? false : true; // change direction variable
			// switch traffic lights
			if (dirToIsland) {
				ml = green;
			} else {
				il = green;
			}
		}
	}
}

