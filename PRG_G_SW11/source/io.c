/*
 * io.c
 *
 *  Created on: 27.11.2020
 *      Author: Dominic Sonderegger, Jonas Augustin
 */

#include <stdio.h>
#include <stdint.h>
#include "board.h"  // library for the hardware
#include "lib/sseg_ctrl.h"  // library for 7seg display
#include "stack.h"

void nextInput(void) {
	element_t val = { .type = 1, .value = 0 };
	element_t op = { .type = 2, .value = 0 };

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
		Push(val);
	} else if (getSW4()) {
		Push(op);
	}
}

void displayResult(void) {
	uint8_t result = 0; // used to typecast int32_t to uint8_t
	char error_letter = 'E'; // Character to display "E" for error
	char error_number = 0;   // the error number received form calc.c

	element_t outp = { .type = 0, .value = 0 }; // Initialize element to save stack value

	StackError_t stackError = Peek(&outp); // get result from calc.c

	if(stackError != STACK_NO_ERROR) { // error while peeking
			printf("Unable to display result, Stack Error: %d\n", stackError);
			outp.type = error;
			outp.value = 9;
	}

	if (outp.type == number) {
		if (outp.value < 0) { // is value
			PWM_SetDutycycleRed(100); // switch on red LED to indicate negative result

			if (outp.value < -256) { // check if the result can be parsed to char
				result = outp.type * -1; // make value positive and parse it to char type
				setBothSSEGnum(result);
			} else {
				printf("Unable to display result <%d>, Result out of range.\n", result);
			}
		} else if (outp.value >= 0) {
			PWM_SetDutycycleRed(0); // switch off red LED to indicate positive result

			if (outp.value < 256) { // check if the result can be parsed to char
				result = outp.type; // parse it to char type
				printf("Unable to display result <%d>, Result out of range.\n", result);
			} else {
				printf("result out of display range\n");
			}
		}
	} else if (outp.type == error) {
		error_number = outp.value; // parse to char
		setSSEGchar(2, error_number);
		setSSEGchar(1, error_letter);
		Clear(); // clear stack after error
	}
}

