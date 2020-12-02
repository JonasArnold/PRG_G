/*
 * io.h
 *
 *  Created on: 27.11.2020
 *      Author: Dominic Sonderegger, Jonas Augustin
 */

#ifndef IO_H_
#define IO_H_

#include <stdbool.h>
#include "stack.h"
#include "calc.h"

// checks if a switch was pressed
// reads out number if SW3 was pressed
// reads out operator if SW4 was pressed
// puts this information on the stack as element_t (defined in calc.h)
// returns true if a new input happened
extern bool nextInput(void);

// displays the result on the hardware
// peeks the stack
// if it is a number => display the number
// -> if the number is negative rgb led is red
// if it is an error => display the error code on the 7seg (E + error code)
// -> delete stack after the error code was displayed
extern void displayResult(void);

#endif /* IO_H_ */
