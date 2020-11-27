/*
 * stack.h
 *
 *  Created on: 27.11.2020
 *      Author: Jonas Arnold
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdint.h>   /* for standard integer types */
#include <stdbool.h>  /* for bool */
#include <stddef.h>   /* for size_t */

/* Definition of Element type */
typedef int32_t num_t;

typedef enum{
	unknown, number, operator, error
} value_type_t;

typedef struct{
	value_type_t type;  // defines what the value is
	num_t value;
} element_t;

/* Definition of Stack types */
typedef enum {
	STACK_NO_ERROR=0, 		/* no error */
	STACK_OVERFLOW_ERROR, 	/* stack overflow */
	STACK_UNDERFLOW_ERROR,	/* stack underflow */
	STACK_NO_MEMORY,        /* not able to allocate memory for stack */
	STACK_REALLOC_ERROR,    /* not allowed to allocate memory again */
} StackError_t;

typedef element_t Stack_t;

/* Initializes the stack, returns error code */
extern StackError_t Init(size_t stackSize);

/* Deinitializes the stack, returns error code */
extern StackError_t DeInit(void);

/* Puts an element on top of the stack, returns error code */
extern StackError_t Push(Stack_t newElement);

/* Returns an removes the top element from the stack, returns error code */
extern StackError_t Pop(Stack_t *stackElementp);

/* Returns the top element from the stack without removing it, returns error code */
extern StackError_t Peek(Stack_t *stackElementp);

/* Returns true if the stack is empty */
extern bool isEmpty(void);

/* Returns true if the stack is full */
extern bool isFull(void);

#endif /* STACK_H_ */
