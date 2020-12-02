/*
 * sw11.c
 * Authors: Collin Bos, Dominic Sonderegger, Jonas Augustin, Jonas Arnold
 */

#include <stdio.h>

#include "board.h"
#include "io.h"
#include "calc.h"
#include "stack.h"

int main(void) {
	init();

	// initialize Stack
	Init(10);

	// endless loop
	while(true){
		if(nextInput()){  // io.h
			calculate();  // calc.h
		}
	}  // end while true

	return 0;
}
