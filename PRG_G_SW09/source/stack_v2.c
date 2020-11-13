/*
 * stack_v2.c
 *
 *  Created on: 13.11.2020
 *      Author: jonas
 */

#include "main.h"

#ifdef VERSION_2

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "stack_v2.h"

// Constants
#define STACK_SIZE 10

// Variables
static uint8_t data[STACK_SIZE];  // stack
static uint8_t index = 0; // first free element
// index = {1...STACK_SIZE} stack is not empty
// index = 0 stack is empty
// index > STACK_SIZE: ERROR

void Init(){
	// clear all elements
	for(int i = 0; i < STACK_SIZE; i++){
		data[i] = 0;
	}
	index = 0;
} // Init()

bool isEmpty(){
	return (index == 0);
} // isEmpty()

bool isFull(){
	return (index >= STACK_SIZE);
} // isFull()


StackStatus_t Push(uint8_t val){
	// check if stack is full
	if( isFull() ){
		printf("Push() not allowed, Stack is full\n");
		return ERROR_OVERFLOW;
	}
	data[index++] = val;
	return OK;
} // Push()

uint8_t Pop(StackStatus_t *status){
	// check if stack is empty
	if( isEmpty() ){
		printf("Pop() not allowed, Stack is empty\n");
		*status = ERROR_UNDERFLOW;
		return 0;
	}

	index--;  // go back to last written element
	uint8_t tmp = data[index];
	data[index] = 0;
	*status = OK;
	return tmp;
} // Pop()

uint8_t Peek(void){
	if( isEmpty() ){ // not written any element yet
		printf("Peek() not allowed, Stack is empty\n");
		return 0;
	}
	return data[index-1];

} // Peek()

#endif /* VERSION_2 */
