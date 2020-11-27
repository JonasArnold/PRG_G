/*
 * delay.c
 *
 *  Created on: 13.02.2020
 *      Author: Pascal Jund
 */

#include <stdint.h>
#include "delay.h"


#define CLK_FREQ 20971520 	/* Click Frequency in Hz */
#define CC_LOOP 11			/* Clock Cycles per for Loop */

void delay_ms(uint32_t t){
	uint32_t cycles = (uint32_t) ((float)t * CLK_FREQ / 1e3 / CC_LOOP);
	for(uint32_t i = 0U; i < cycles; i++){
		__asm("NOP");
	}
}

void delay_us(uint32_t t){
	uint32_t cycles = (uint32_t) ((float)t * CLK_FREQ / 1e6 / CC_LOOP);
	for(uint32_t i = 0U; i < cycles; i++){
		__asm("NOP");
	}
}
