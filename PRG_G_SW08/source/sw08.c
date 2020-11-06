/**
 * @file    sw08.c
 * @brief   Solution to homework SW08.
 */


/* Bericht Semesterwoche 8
 *
 * Die Implementierung beider Funktionen verlief gut.
 * Funktionspointer kannte ich noch nicht. Ich finde die Definierung
 * mit typedef uebersichtlicher.
 * Rekursion kannte ich bereits vor PRG.
 *
 */



#include "board.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

void Aufg_8_2(void);
void Aufg_8_3(void);

int main(void) {

	init();

	printf("************INTERGRAL************\n\n");
	Aufg_8_2();

	printf("\n\n************FIBONACCI************\n\n");
	Aufg_8_3();

	return 0;
}


/****************************************************************
 * AUFGABE 8.2
 * INTEGRAL
 ****************************************************************/

// create type for function pointer
typedef uint32_t (fun_t) (uint32_t);

// declare some example calculation functions
static fun_t plusTwo, timesFour, plus5DivBy2;
// declare integration function
static uint32_t integrate(fun_t *function, uint32_t a, uint32_t b, uint32_t deltaX);

void Aufg_8_2()
{
	int result = 0;

	// try to integrate (x+2) from 5 to 8 with step width 1
	result = integrate(plusTwo, 5, 8, 1);
	printf("Result of integral 5->8 (x+2) deltaX=1: \t%d\n", result);

	result = integrate(timesFour, 3, 9, 2);
	printf("Result of integral 3->9 (4x) deltaX=2: \t%d\n", result);

	result = integrate(plus5DivBy2, 2, 4, 1);
	printf("Result of integral 2->4 ((x+5)/2) deltaX=1: \t%d\n", result);
}

/*
 * Integrates the function that was passed via the function pointer.
 * step is the step width to intergrate with.
 * a is the lower, b is the upper border of the integral.
 * a has to be lower than b!!
 */
static uint32_t integrate(fun_t *function, uint32_t a, uint32_t b, uint32_t deltaX){
	if(a > b){
		printf("not implemented!");
		return;
	}

	int sum = 0;
    for(uint32_t i = a; i < b; i+= deltaX){
       sum += (deltaX * function(i));  // calculate integral
    }
    return sum;
}


/* Example functions */
static uint32_t plusTwo(uint32_t x){
   return x+2;
}

static uint32_t timesFour(uint32_t x){
	return (4*x);
}

static uint32_t plus5DivBy2(uint32_t x){
  return ((x+5)/2);
}


/****************************************************************
 * AUFGABE 8.3
 * FIBONACCI
 ****************************************************************/

uint32_t fibonacci(uint32_t n);

void Aufg_8_3()
{
	uint32_t result, n = 8;

	result = fibonacci(n);
	printf("Fibonacci(%d) = %d\n", n, result);
}

uint32_t fibonacci(uint32_t n)
{
	// f0 = 0, f1 = 1
    if(n<2){
    	return n;
    }

    return (fibonacci(n-1) + fibonacci(n-2));
}
