/*
 * tilt.c
 *
 *  Created on: 13 Sep 2019
 *      Author: JumpStart
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

void TILT_Init(){

    static const gpio_pin_config_t SW_configInput = {
      kGPIO_DigitalInput,  /* use as output pin */
      0,  /* initial value */
    };

	GPIO_PinInit(GPIOE, 1U, &SW_configInput);

}

bool getTilt(){
	return !GPIO_PinRead(GPIOE, 1U);
}
