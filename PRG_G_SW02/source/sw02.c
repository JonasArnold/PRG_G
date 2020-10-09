/**
 * @file    sw02.c
 * @brief   Solution to homework SW02.
 */

#include "board.h"
#include <stdio.h>

uint8_t state = 0; // 0 = waiting for button press, 1 = button was pressed, 2 = blinking ongoing, 3 = blinking finished
uint8_t blink_seq_left = 10; // down counter for number of blink procedures left
uint8_t button_pressed = 0; // which button was pressed. 0 = undef., 1 = button 1, 2 = button 2
uint8_t blink_cycles = 0;   // number of blinks

int blink_delay_ms = 150; // delay between blink

void switchCorrectLed(uint8_t on, uint8_t ledNumber);

int main(void) {

	init();
	printf("Waiting for button press...\n");

	// only loop if there are blink procedures left
	while (blink_seq_left > 0) {

		// state machine
		switch (state) {
		case 0:  // waiting for button press
			if (getSW3()) {
				button_pressed = 1;
				printf("Button 1 was pressed\n");
			}
			if (getSW4()) {
				button_pressed = 2;
				printf("Button 2 was pressed\n");
			}
			if (button_pressed > 0) {
				state = 1;  // next state
			}
			break;

		case 1:  // button was pressed
			blink_cycles = (getSW1() ? 0 : 1);   // set to 1 if sw1 is on
			blink_cycles += (getSW2() ? 0 : 2);  // add 2 if sw2 is on
			printf("Blink cycles according to switches: %i\n", blink_cycles);

			state = 2;  // next state
			printf("Blink sequence ongoing...\n");
			break;

		case 2:  // blinking ongoing
			if (blink_cycles > 0) {
				switchCorrectLed(1, button_pressed);
				delay_ms(blink_delay_ms);
				switchCorrectLed(0, button_pressed);
				delay_ms(blink_delay_ms);
				blink_cycles--;
			} else {
				printf("Blink sequence finished\n");
				state = 3;  // next state
			}
			break;

		case 3:  // blinking finished
			state = 0;
			blink_seq_left--;

			// make sure the buttons are not pressed anymore (wait until not pressed anymore)
			if(button_pressed == 1)
			{
				while(getSW3()) {}
			}
			else if(button_pressed == 2)
			{
				while(getSW4()) {}
			}
			button_pressed = 0;

			// print only if there are blink sequences left
			if(blink_seq_left > 0){
				printf("Waiting for button press...\n");
			}

			break;
		}
	}

	printf("Maximum blink sequences reached.\n");

	return 0;
}

/* Switches on or off the LED according the number that was pressed */
void switchCorrectLed(uint8_t on, uint8_t ledNumber) {
	printf("Setting LED %i to %s\n", ledNumber, on ? "on" : "off");
	if (ledNumber == 1) {
		if (on == 1) {
			setLED1();
		} else {
			clearLED1();
		}
	} else if (ledNumber == 2) {
		if (on == 1) {
			setLED2();
		} else {
			clearLED2();
		}
	}
}
