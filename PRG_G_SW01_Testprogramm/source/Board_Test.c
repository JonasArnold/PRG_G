/*
 * Board_Test.c
 *
 *  Created on: 13 Sep 2019
 *      Author: Luca Imesch
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK22F51212.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_adc16.h"
#include "fsl_ftm.h"
#include "fsl_dac.h"
#include "adc.h"
#include "sw.h"
#include "pwm.h"
#include "led.h"
#include "sseg.h"
#include "dac.h"
#include "tilt.h"
#include "delay.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint8_t redDutycycle 	= 80U;
volatile uint8_t blueDutycycle 	= 80U;
volatile uint8_t greenDutycycle = 80U;

enum states{
	LED1 = 0,
	LED2 = 1,
	RGB_RED = 2,
	RGB_BLUE = 3,
	RGB_GREEN = 4,
	SSEG1 = 5,
	SSEG2 = 6,
	SPEAKER = 7,
	SW1 = 8,
	SW2 = 9,
	SW3 = 10,
	SW4 = 11,
	TILT = 12,
	POTI = 13,
	LIGHT = 14,
	DONE = 15
}state;

void Board_Test(){
	volatile uint32_t i = 0U;

	switch (state){

	case LED1:
		printf("LED1 on \n");
		setLED1();
		delay();
		printf("LED1 off \n");
		clearLED1();
		delay();
		state++;
		break;

	case LED2:
		printf("LED2 on \n");
		setLED2();
		delay();
		printf("LED2 off \n");
		clearLED2();
		delay();
		state++;
		break;

	case RGB_RED:
		printf("RGB LED RED on \n");
		PWM_SetDutycycleRed(redDutycycle);
		delay();
		printf("RGB LED RED off \n");
		PWM_SetDutycycleRed(0);
		delay();
		state++;
		break;

	case RGB_BLUE:
		printf("RGB LED BLUE on \n");
		PWM_SetDutycycleBlue(blueDutycycle);
		delay();
		printf("RGB LED BLUE off \n");
		PWM_SetDutycycleBlue(0);
		delay();
		state++;
		break;

	case RGB_GREEN:
		printf("RGB LED GREEN on \n");
		PWM_SetDutycycleGreen(greenDutycycle);
		delay();
		printf("RGB LED GREEN off \n");
		PWM_SetDutycycleGreen(0);
		delay();
		state++;
		break;

	case SSEG1:
		printf("7-Segment Left on \n");
	    setSSEG1A();
	    setSSEG1B();
	    setSSEG1C();
	    setSSEG1D();
	    setSSEG1E();
	    setSSEG1F();
	    setSSEG1G();
	    setSSEG1DP();
		delay();
		printf("7-Segment Left off \n");
	    clearSSEG1A();
	    clearSSEG1B();
	    clearSSEG1C();
	    clearSSEG1D();
	    clearSSEG1E();
	    clearSSEG1F();
	    clearSSEG1G();
	    clearSSEG1DP();
		delay();
		state++;
		break;

	case SSEG2:
		printf("7-Segment Right on \n");
	    setSSEG2A();
	    setSSEG2B();
	    setSSEG2C();
	    setSSEG2D();
	    setSSEG2E();
	    setSSEG2F();
	    setSSEG2G();
	    setSSEG2DP();
		delay();
		printf("7-Segment Right off \n");
	    clearSSEG2A();
	    clearSSEG2B();
	    clearSSEG2C();
	    clearSSEG2D();
	    clearSSEG2E();
	    clearSSEG2F();
	    clearSSEG2G();
	    clearSSEG2DP();
		delay();
		state++;
		break;

	case SPEAKER:
		printf("Speaker on \n");
	    for (i = 0U; i < 2000U; ++i)
	    {
	    	DAC0_setValue(0x00);
	    	delay_us(2000-i);
	    	DAC0_setValue(0xfff);
	    	delay_us(2000-i);
	    }
	    printf("Speaker off \n");
	    delay();
	    state++;
	    break;

	case SW1:
		printf("Press SW1 \n");
		while(!getSW1()){

		}
		state++;
		printf("SW1 pressed \n");
		break;

	case SW2:
		printf("Press SW2 \n");
		while(!getSW2()){

		}
		state++;
		printf("SW2 pressed \n");
		break;

	case SW3:
		printf("Press SW3 \n");
		while(!getSW3()){

		}
		state++;
		printf("SW3 pressed \n");
		break;

	case SW4:
		printf("Press SW4 \n");
		while(!getSW4()){

		}
		state++;
		printf("SW4 pressed \n");
		break;

	case TILT:
		printf("Tilt the Board Sideways \n");
		while(!getTilt()){}
		state++;
		printf("Board Tilted \n");
		break;

	case POTI:
	    for (i = 0U; i < 200U; ++i)
	    {
			printf("Potentiometer Value: %d \n", ADC0_GetValue());
			ADC0_Start();
	    }
		state++;
		break;

	case LIGHT:
	    for (i = 0U; i < 200U; ++i)
	    {
			printf("Light Sensor Value: %d \n", ADC1_GetValue());
			ADC1_Start();
	    }
		state++;
		break;

	case DONE:
		printf("Board Test Complete");
		state++;
		break;

	}
}
