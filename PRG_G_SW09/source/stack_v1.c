/*
 * stack_v1.c
 *
 *  Created on: 13.11.2020
 *      Author: jonas
 */

#include "main.h"

#ifdef VERSION_1

#include <stdint.h>
#include <stdio.h>

#include "stack_v1.h"

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

void Push(uint8_t val){
	// check if stack is full
	if(index >= STACK_SIZE){
		printf("Push() not allowed, Stack is full\n");
		return;
	}
	data[index++] = val;
} // Push()

uint8_t Pop(void){
	// check if stack is empty
	if(index == 0){
		printf("Pop() not allowed, Stack is empty\n");
		return 0;
	}

	index--;  // go back to last written element
	uint8_t tmp = data[index];
	data[index] = 0;
	return tmp;
} // Pop()

uint8_t Peek(void){
	if(index == 0){ // not written any element yet
		printf("Peek() not allowed, Stack is empty\n");
		return 0;
	}
	return data[index-1];

} // Peek()

#endif /* VERSION_1 */
