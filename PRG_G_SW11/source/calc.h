/*
 * calc.h
 *
 *  Created on: 27.11.2020
 *      Author: Colin Bos, Jonas Arnold
 */

#ifndef CALC_H_
#define CALC_H_

#include <stdint.h>
#include "io.h"

typedef enum{
	missing_operant, division_by_0, operand_nan, overflow
} calc_error_t;

// peeks the stack
// if the first element is a number => do nothing
// if the first element is an operator:
// -> pop the three newest elements from the stack:
//    1. operator ('+', '-', '*', '%' (ASCII))
//    2. operand 1 (integer number)
//    3. operand 2 (integer number)
// -> calculate the result
// -> push result as element_t onto the stack
// -> call displayResult
extern void calculate(void);

#endif /* CALC_H_ */
