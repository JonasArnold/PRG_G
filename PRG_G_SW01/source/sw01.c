/**
 * @file    sw01.c
 * @brief   First Steps ;-)
 */

#include "board.h"
#include <stdio.h>
#include <stdbool.h>
#include <delay.h>

int main(void) {

	int counter = 0;
	init();

	/* LED0 : blue led on TinyK22 board */

	while (true) {
		setLED0();
		delay_ms(200);
		clearLED0();
		delay_ms(600);

		counter++;
		printf("Iteration fertig. Count: %i \n", counter);
	}

	return 0;
}
