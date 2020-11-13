/*
 * STACK V2 Header File
 * Defines the interface for the Stack V2.
 */

// INLCUDES
#include <stdint.h>  // include integer types
#include <stdbool.h>  // include boolean types

#ifndef STACK_V2_H  // Protection against recursive includes
#define STACK_V2_H

	// Stack status enum
	typedef enum {
		OK = 0,
		ERROR_OVERFLOW = 1,
		ERROR_UNDERFLOW = 2
	} StackStatus_t;

	/* Declarations */
	extern void Init(void);
	extern bool isEmpty();
	extern bool isFull();
	extern StackStatus_t Push(uint8_t);
	extern uint8_t Pop(StackStatus_t*);
	extern uint8_t Peek(void);

#endif  /* STACK_V2_H */
