/*
 * led.c
 *
 *  Created on: 12 Sep 2019
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

void setLED0(){
	GPIO_PortClear(GPIOC, 1U<<2);
}

void setLED1(){
	GPIO_PortSet(GPIOA, 1U<<2);
}

void setLED2(){
	GPIO_PortSet(GPIOA, 1U<<1);
}

void clearLED0(){
	GPIO_PortSet(GPIOC, 1U<<2);
}

void clearLED1(){
	GPIO_PortClear(GPIOA, 1U<<2);
}

void clearLED2(){
	GPIO_PortClear(GPIOA, 1U<<1);
}

void toggleLED0(){
	GPIO_PortToggle(GPIOC, 1U<<2);
}

void toggleLED1(){
	GPIO_PortToggle(GPIOA, 1U<<2);
}

void toggleLED2(){
	GPIO_PortToggle(GPIOA, 1U<<1);
}
