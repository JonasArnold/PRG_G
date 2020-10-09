/**
 * @file    sw04.c
 * @brief   Solution to homework SW04.
 */

#include "board.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void getBinaryString(char *buffer, unsigned char num);

int main(void) {

	init();

	uint8_t n = 0;
	do {
		/* compute code */
		uint8_t gray = n ^ (n >> 1); // n XOR (n/2)

		/* print values to console -- version A */
		char bufferA[9] = {0};
		getBinaryString(bufferA, gray);
		printf("(A) %3d : %3d => %8s\n", n, gray, bufferA);

		/* print values to console -- version B */
		char bufferB[9] = {0};
		itoa(gray, bufferB, 2);  // integer to string conversion on base 2
		printf("(B) %3d : %3d => %8s\n\n", n, gray, bufferB);

		/* show values on 7-segment display */
		bufferA[7] == '1' ? setSSEG1E() : clearSSEG1E();
		bufferA[6] == '1' ? setSSEG1F() : clearSSEG1F();
		bufferA[5] == '1' ? setSSEG1A() : clearSSEG1A();
		bufferA[4] == '1' ? setSSEG2A() : clearSSEG2A();
		bufferA[3] == '1' ? setSSEG2B() : clearSSEG2B();
		bufferA[2] == '1' ? setSSEG2C() : clearSSEG2C();
		bufferA[1] == '1' ? setSSEG2D() : clearSSEG2D();
		bufferA[0] == '1' ? setSSEG1D() : clearSSEG1D();

		delay_ms(100); /* optional */
		n = n + 1;
	} while (n != 255);

	while(1);   // endless loop

	return 0;
}


/* Prints an 1 byte number in binary to the console, also adds newline after the number. */
void getBinaryString(char *buffer, unsigned char num)
{
	for(int8_t e = 7; e >= 0; e--)  // iterate exponent from 7 -> 0
	{
		uint8_t twoSquared = (1<<e); // 2^e (needs to be unsigned!)
		if(num >= twoSquared)   // num bigger than 2^n
		{
			buffer[7-e] = '1';
			num -= twoSquared;  // subtract 2^n from num
		}
		else
		{
			buffer[7-e] = '0';
		}
	}
}

