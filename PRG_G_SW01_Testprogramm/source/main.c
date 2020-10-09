/**
 * @file    main.c
 * @brief   PRG_G Template.
 */

#include "board.h"
#include <stdio.h>
#include "Board_Test.h"

int main(void) {
	init();
	printf("Hello World\n");

	while(true){
		Board_Test();
	}
	return 0;
}

