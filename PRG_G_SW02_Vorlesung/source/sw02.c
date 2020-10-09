/**
 * @file    sw02.c
 * @brief   Solution to homework SW02.
 */

#include "board.h"
#include <stdio.h>

int numberOfBlinks = 5;
int timePerBlinkMs = 1000;

int main(void) {

	init();

	while (1) {
		if (getSW1() == 1) {  // true when switch is active
			numberOfBlinks = 10;
		} else {
			numberOfBlinks = 5;
		}

		for (int i = 0; i < numberOfBlinks; ++i) {  // loop for blinks
			setLED1();
			delay_ms(timePerBlinkMs / 2);
			clearLED1();
			delay_ms(timePerBlinkMs / 2);
		}

		delay_ms(5000);  //END
	}

	return 0;
}
