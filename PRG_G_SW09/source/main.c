/*
 * main.c
 *
 *  Created on: 13.11.2020
 *      Author: jonas
 */

/* Bericht SW09:
 * Die Templates haben nicht kompiliert, deshalb war ich anfangs sehr verwirrt.
 * Diese Test Funktionen waren nicht hilfreich, sie haben nur weiter verwirrt.
 * In der Vorlesung sind wir dann leider trotzdem sehr spät auf das dieswoechige Thema eingegangen.
 * Allerdings wurde es da gut erklaert.
 *
 * In der Vorlesung wurde leider nicht gezeigt wie es mit mehreren Versionen zu handhaben ist.
 * Wenn man Funktionen mit dem selben Namen in mehreren .c files definiert dann gibt es beim kompilieren fehler.
 * Ich habe dies mit einem Workaround geloest und eine main.h Datei erstellt wo man festlegen kann welche Version
 * kompiliert werden soll.
 *
 * Fuer mich war diese Woche nichts neues dabei, Header und Praeprozessor kannte ich schon.
 * Ausserhalb der Vorlesungszeit hatte ich ca. 1h Aufwand.
 */

#include <stdio.h>
#include "board.h"
#include "main.h"

/* Select version to use in main.h !! */

#ifdef VERSION_1
#include "stack_v1.h"

void main(void){
	init();  // init board

	Init();  // init stack

	printf("Peek() = %d\n", Peek());
	printf("Pushing 42 to stack\n");
	Push(42);
	printf("Pushing 55 to stack\n");
	Push(55);
	printf("Peek() = %d\n", Peek());
	printf("Pop() = %d\n", Pop());
	printf("Peek() = %d\n", Peek());
}
#endif  /* VERSION_1 */

#ifdef VERSION_2
#include "stack_v2.h"

void main(void){
	init();  // init board

	Init();  // init stack

	printf("Peek() = %d\n", Peek());
	printf("Pushing 42 to stack\n");
	Push(42);

	printf("Peek() = %d\n", Peek());

	StackStatus_t status = OK;
	printf("Pop() = %d\n", Pop(&status));

	// provocate error underflow
	printf("Pop() = %d\n", Pop(&status));
	printf("After Pop() StackStatus: %d\n", status);

	for(int i = 0; i <= 11; i++)
	{
		StackStatus_t status = Push(i);  // push numbers to stack
		printf("Pushing %d reported status %d\n", i, status);
	}

	printf("Peek() = %d\n", Peek());
}
#endif  /* VERSION_2 */
