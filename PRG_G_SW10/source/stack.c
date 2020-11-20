/* stack.c, implement a stack with dynamic memory allocation */


/*
 * Bericht SW10
 * Die Wiederverwendung des Codes von letzter Woche finde ich sinnvoll. So koennen wir uns auf die Unit tests fokussieren.
 * Ich habe selber schon viele Unit tests geschrieben in C#, deshalb ist das kein Neuland mehr fuer mich.
 * Ich hoffe, dass wir naechste Woche noch selber Unit tests schreiben koennen, das waere ja dann bei einer Entwicklung
 * auch so.
 *
 * Bezueglich meines Codes von dieser Woche:
 * Implementierung lief problemlos, ich konnte den Code von letzter Woche mehr oder weniger uebernehmen.
 * 2 Tests beim Advanced failen, ich weiss auch warum:
 * IsEqual(Init(0), STACK_NO_ERROR) sollte meiner Meinung nach nicht NoError zurueckgeben, da ja kein Memory alloziert werden kann so
 * IsEqual(DeInit(), STACK_NO_ERROR) funktioniert entsprechend auch nicht, da ja kein Memory alloziert wurde
 * Diese Probleme koennte ich problemlos loesen, z.B. mit einer Variablen, die sich merkt ob schon initialisiert wurde.
 * Aber wie schon erwaehnt eigentlich sollte eine initialisierung mit Size 0 nach meiner Meinung nicht NoError zurueckgeben.
 * Deshalb habe ich es so gelassen.
 * Vielleicht koennten Sie ja naechste Woche erklaeren warum das NoError zurueckgeben soll.
 *
 * Resultate Unit Tests:
 * Testcases: failed: 1
 *            passed: 3
 * Checks:    failed: 2
 *            passed: 1663
 *
 */



#include "stack.h"
#include <stdlib.h> /* for malloc() */
#include <stdio.h>  /* for printf */

// Variables
static Stack_t *data;  // stack
static uint16_t index = 0; // first free element
// index = {1...stackSize} stack is not empty
// index = 0 stack is empty
// index > stackSize: ERROR
static size_t stackSize = 0;  // number of max elements in stack

/* Is stack is empty ? */
bool isEmpty(void) {
	return index == 0;
}

/* Is stack is full ? */
bool isFull(void) {
	return index >= stackSize;
}

/* Puts an element on top of the stack */
StackError_t Push(Stack_t newElement) {
	// check if stack is full
	if( isFull() ){
		printf("Push() not allowed, Stack is full\n");
		return STACK_OVERFLOW_ERROR;
	}
	data[index++] = newElement;
	return STACK_NO_ERROR;
}

/* Returns and removes the top element from the stack */
StackError_t Pop(Stack_t *pStackElement){
	// check if stack is empty
	if( isEmpty() ){
		printf("Pop() not allowed, Stack is empty\n");
		return STACK_UNDERFLOW_ERROR;
	}

	index--;  // go back to last written element
	Stack_t tmp = data[index];
	data[index] = 0;
	*pStackElement = tmp;
	return STACK_NO_ERROR;
}

/* Returns top element from the stack without removing it */
StackError_t Peek(Stack_t *pStackElement) {
	if( isEmpty() ){ // not written any element yet
		printf("Peek() not allowed, Stack is empty\n");
		return STACK_UNDERFLOW_ERROR;
	}
	*pStackElement = data[index-1];
 	return STACK_NO_ERROR;
}

/* Initializes the stack */
StackError_t Init(size_t pStackSize) {
	if(data == NULL) { // not yet initialized
		data = calloc(pStackSize, sizeof(Stack_t)); // try to allocate memory
		if(data == NULL){
			// ERROR since calloc failed to allocate memory
			return STACK_NO_MEMORY;
		}
		stackSize = pStackSize; // store max elements
		return STACK_NO_ERROR;

	} else{ // already initialized
		// double init error
		return STACK_REALLOC_ERROR;
	}
}

/* Deinitializes the stack, returns error code */
StackError_t DeInit(void) {
	if(data != NULL) {  // memory was allocated
		free(data);
		data = NULL;
		return STACK_NO_ERROR;
	} else{ // data is NULL
		// else not initialized: error
		return STACK_NO_MEMORY;
	}
}
