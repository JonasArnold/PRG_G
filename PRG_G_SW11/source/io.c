/*
 * io.c
 *
 *  Created on: 27.11.2020
 *      Author: Dominic Sonderegger, Jonas Augustin
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "board.h"  // library for the hardware
#include "lib/sseg_ctrl.h"  // library for 7seg display
#include "stack.h"

bool nextInput(void) {
	element_t val = { .type = 1, .value = 0 };
	element_t op = { .type = 2, .value = 0 };
	StackError_t stackError = STACK_NO_ERROR;
	bool inputHappened = false;

	if (getSW1()) {
		if (getSW2()) {
			op.value = '/';
			val.value = 3;
		} else if (!getSW2()) {
			op.value = '*';
			val.value = 2;
		}
	} else if (!getSW1()) {
		if (getSW2()) {
			op.value = '-';
			val.value = 1;
		} else if (!getSW2()) {
			op.value = '+';
			val.value = 0;
		}
	}


	if (getSW3()) {
		while(getSW3()){ delay_ms(50); }  // debouncing the button press
		stackError = Push(val);
		if(stackError != STACK_NO_ERROR) { // error while pushing
				printf("io.c => nextInput(): Failed to push new number to stack, Stack Error: %d\n", stackError);
		}
		inputHappened = true;
	} else if (getSW4()) {
		while(getSW4()){ delay_ms(50); }  // debouncing the button press
		stackError = Push(op);
		if(stackError != STACK_NO_ERROR) { // error while pushing
				printf("io.c => nextInput(): Failed to push new operator to stack, Stack Error: %d\n", stackError);
		}
		inputHappened = true;
	}

	return inputHappened;
}

void displayResult(void) {
	uint8_t result = 0; // used to typecast to uint8_t
	char error_letter = 'E'; // Character to display "E" for error
	char error_number = 0;   // the error number received form calc.c

	element_t outp = { .type = 0, .value = 0 }; // Initialize element to save stack value
	StackError_t stackError = Peek(&outp); // get result from calc.c

	if(stackError != STACK_NO_ERROR) { // error while peeking
			printf("io.c => displayResult(): Failed to get element from stack, Stack Error: %d\n", stackError);
			outp.type = error;
			outp.value = 9;
	}

	if (outp.type == number) {
		// check if number too big
		if(outp.value >= 100 || outp.value <= -100){
			printf("io.c => displayResult(): Unable to display, result <%d> out of range.\n", result);
			return; // end
		}

		if (outp.value < 0) { // is value smaller than 0
			PWM_SetDutycycleRed(100); // switch on red LED to indicate negative result (duty cycle 100 = led on)
			result = (outp.value * (-1)); // make value positive and cast it to char type
		} else{
			PWM_SetDutycycleRed(0); // switch off red LED to indicate positive result (duty cycle 0 = led off)
			result = outp.value; // cast to char type
		}

		// display the number
		setBothSSEGnum(result);

	} else if (outp.type == error) {
		error_number = outp.value; // cast to char
		setSSEGchar(2, error_number);
		setSSEGchar(1, error_letter);
		Clear(); // clear stack after error
	}
}

