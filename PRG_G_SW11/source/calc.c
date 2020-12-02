/*
 * calc.c
 *
 *  Created on: 27.11.2020
 *      Author: Collin Bos, Jonas Arnold
 */

#include <stdio.h>  // for printf
#include <stdbool.h>
#include "calc.h"
#include "io.h"
#include "stack.h"

// internal functions
static void pushError(calc_error_t error);

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
void calculate(void){

	// peek the stack to see what is inside
	Stack_t stackElement;
	StackError_t stackError = Peek(&stackElement);
	if(stackError != STACK_NO_ERROR){
		// if there was an error reading out the stack => don't do anything
		printf("calc.c => calculate(): failed reading out stack. Stack Error: %d\n", stackError);
		return;
	}

	// only do something if the peeked element is of type operator
	if(stackElement.type == operator){
		Stack_t operator, operand1, operand2;

		/****** Get values from stack ******/
		// pop operator
		stackError = Pop(&operator);
		if(stackError){
			printf("calc.c => calculate(): failed to get operator element from stack. Stack Error: %d\n", stackError);
			return;
		}

		// pop operand1
		stackError = Pop(&operand1);
		if(stackError){
			printf("calc.c => calculate(): failed to get operand1 element from stack. Stack Error: %d\n", stackError);
			pushError(missing_operant);
			return;
		}
		if(operand1.type != number){ // check if it is a number
			printf("calc.c => calculate(): operand1 is not a number\n");
			pushError(operand_nan);
			return;
		}

		// pop operand2
		stackError = Pop(&operand2);
		if(stackError){
			printf("calc.c => calculate(): failed to get operand2 element from stack. Stack Error: %d\n", stackError);
			pushError(missing_operant);
			return;
		}
		if(operand2.type != number){ // check if it is a number
			printf("calc.c => calculate(): operand2 is not a number\n");
			pushError(operand_nan);
			return;
		}

		/****** calculate the result ******/
		num_t result = 0;
		switch(operator.value)
		{
		case '+':
			result = operand1.value + operand2.value;
			break;

		case '-':
			result = operand2.value - operand1.value;
			break;

		case '*':
			result = operand1.value * operand2.value;
			break;

		case '/':
			if(operand1.value == 0){
				printf("calc.c => calculate(): division by zero\n");
				pushError(division_by_0);
				return;
			}

			result = operand2.value / operand1.value;
			break;
		default:
			printf("calc.c => calculate(): operator is unknown character\n");
			break;
		}

		/****** push result to stack and let it display ******/
		element_t resultElement = { .type = number, .value = result };
		StackError_t stackError = Push(resultElement);
		if(stackError != STACK_NO_ERROR) { // error while pushing
			printf("calc.c => calculate(): failed to push result to stack. Stack Error: %d\n", stackError);
			return;
		}
		displayResult();
	}
	else if(stackElement.type == number){
		// display the number on the display
		displayResult();
	}
}

/*
 * Generate new Error element with error_val from enum calc_error_t.
 * Tries to push it to the stack and checks if this failed.
 * After pushing the error to the stack, display the result.
 */
static void pushError(calc_error_t error_val){
	element_t errorElement = { .type = error, .value = error_val };
	StackError_t stackError = Push(errorElement);
	if(stackError != STACK_NO_ERROR){  // error while pushing
		printf("calc.c => pushError() failed to push errorElement. Stack Error: %d\n", stackError);
	}
	displayResult();
}
