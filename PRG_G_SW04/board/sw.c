/*
 * sw.c
 *
 *  Created on: 11 Sep 2019
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

void SW_Init(){
    static const gpio_pin_config_t SW_configInput = {
      kGPIO_DigitalInput,  /* use as output pin */
      0,  /* initial value */
    };

    GPIO_PinInit(GPIOA, 4U, &SW_configInput);
    GPIO_PinInit(GPIOA, 5U, &SW_configInput);
    GPIO_PinInit(GPIOA, 12U, &SW_configInput);
    GPIO_PinInit(GPIOA, 13U, &SW_configInput);
}

bool getSW1(){
	return GPIO_PinRead(GPIOA, 13U);
}

bool getSW2(){
	return GPIO_PinRead(GPIOA, 12U);
}

bool getSW3(){
	return !GPIO_PinRead(GPIOA, 5U);
}

bool getSW4(){
	return !GPIO_PinRead(GPIOA, 4U);
}
