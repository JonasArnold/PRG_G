/**
 * @file    sseg_ctrl.c
 * @brief   To display characters on one or both SSEG displays of the TinyK22.
 */

#include "board.h"
#include <stdio.h>

void setBothSSEGnum(uint8_t number)
{
	if(number == 0xFF)  // command to clear display
	{
		setSSEGchar(1, 0xFF); setSSEGchar(2, 0xFF);
		printf("Cleared SSEG display\n");
		return;
	}

	if(number > 99)  // cannot display that number
	{
		printf("Cannot display number %i on SSEG.\n", number);
		return;
	}

	if(number >= 10) // only set first digit if this is true
	{
		setSSEGchar(1, number / 10);
	}
	else
	{
		setSSEGchar(1, 0xFF);
	}
	setSSEGchar(2, number % 10);  // always set second digit

	printf("Displaying number %i on SSEG display.\n", number);
}

void setSSEGchar(uint8_t segment, char character)
{
	switch(character)
	{
	case 'A': case 'a': __setSSEGSegments(segment, 1, 1, 1, 0, 1, 1, 1, 0); break;
	case 'B': case 'b': __setSSEGSegments(segment, 0, 0, 1, 1, 1, 1, 1, 0); break;
	case 'C': case 'c': __setSSEGSegments(segment, 1, 0, 0, 1, 1, 1, 0, 0); break;
	case 'D': case 'd': __setSSEGSegments(segment, 0, 0, 1, 1, 1, 1, 1, 0); break;
	case 'E': case 'e': __setSSEGSegments(segment, 1, 0, 0, 1, 1, 1, 1, 0); break;
	case 'F': case 'f': __setSSEGSegments(segment, 1, 0, 0, 0, 1, 1, 1, 0); break;
	case '0': case 0:   __setSSEGSegments(segment, 1, 1, 1, 1, 1, 1, 0, 0); break;
	case '1': case 1:   __setSSEGSegments(segment, 0, 1, 1, 0, 0, 0, 0, 0); break;
	case '2': case 2:   __setSSEGSegments(segment, 1, 1, 0, 1, 1, 0, 1, 0); break;
	case '3': case 3:   __setSSEGSegments(segment, 1, 1, 1, 1, 0, 0, 1, 0); break;
	case '4': case 4:   __setSSEGSegments(segment, 0, 1, 1, 0, 0, 1, 1, 0); break;
	case '5': case 5:   __setSSEGSegments(segment, 1, 0, 1, 1, 0, 1, 1, 0); break;
	case '6': case 6:   __setSSEGSegments(segment, 1, 0, 1, 1, 1, 1, 1, 0); break;
	case '7': case 7:   __setSSEGSegments(segment, 1, 1, 1, 0, 0, 0, 0, 0); break;
	case '8': case 8:   __setSSEGSegments(segment, 1, 1, 1, 1, 1, 1, 1, 0); break;
	case '9': case 9:   __setSSEGSegments(segment, 1, 1, 1, 1, 0, 1, 1, 0); break;
	case '.':   __setSSEGSegments(segment, 0, 0, 0, 0, 0, 0, 0, 1); break;
	case 0xFF:  __setSSEGSegments(segment, 0, 0, 0, 0, 0, 0, 0, 0); break;
	}
}

void __setSSEGSegments(uint8_t segment, uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G, uint8_t DP)
{
	if(segment == 1)
	{
		__setSSEG1Segments(A, B, C, D, E, F, G, DP);
	}
	else if(segment == 2)
	{
		__setSSEG2Segments(A, B, C, D, E, F, G, DP);
	}
	else
	{
		printf("SSEG %i not available.\n", segment);
	}
}

void __setSSEG1Segments(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G, uint8_t DP)
{
	A == 1 ? setSSEG1A() : clearSSEG1A();
	B == 1 ? setSSEG1B() : clearSSEG1B();
	C == 1 ? setSSEG1C() : clearSSEG1C();
	D == 1 ? setSSEG1D() : clearSSEG1D();
	E == 1 ? setSSEG1E() : clearSSEG1E();
	F == 1 ? setSSEG1F() : clearSSEG1F();
	G == 1 ? setSSEG1G() : clearSSEG1G();
	DP == 1 ? setSSEG1DP() : clearSSEG1DP();
}

void __setSSEG2Segments(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G, uint8_t DP)
{
	A == 1 ? setSSEG2A() : clearSSEG2A();
	B == 1 ? setSSEG2B() : clearSSEG2B();
	C == 1 ? setSSEG2C() : clearSSEG2C();
	D == 1 ? setSSEG2D() : clearSSEG2D();
	E == 1 ? setSSEG2E() : clearSSEG2E();
	F == 1 ? setSSEG2F() : clearSSEG2F();
	G == 1 ? setSSEG2G() : clearSSEG2G();
	DP == 1 ? setSSEG2DP() : clearSSEG2DP();
}
