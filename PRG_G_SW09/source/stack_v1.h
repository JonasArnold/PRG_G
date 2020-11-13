/*
 * STACK V1 Header File
 * Defines the interface for the Stack V1.
 */

// INLCUDES
#include <stdint.h>  // include integer types

#ifndef STACK_V1_H  // Protection against recursive includes
#define STACK_V1_H

	/* Declarations */
	extern void Init(void);
	extern void Push(uint8_t);
	extern uint8_t Pop(void);
	extern uint8_t Peek(void);

#endif  /* STACK_V1_H */
