/*
 * dac.c
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

#define DEMO_DAC_BASEADDR DAC0

void DAC0_Init(){

    dac_config_t dacConfigStruct;

	DAC_GetDefaultConfig(&dacConfigStruct);
	DAC_Init(DEMO_DAC_BASEADDR, &dacConfigStruct);
	DAC_Enable(DEMO_DAC_BASEADDR, true);             /* Enable output. */
	DAC_SetBufferReadPointer(DEMO_DAC_BASEADDR, 0U); /* Make sure the read pointer to the start. */
	                                                     /*
	                                                      * The buffer is not enabled, so the read pointer can not move automatically. However, the buffer's read pointer
	                                                      * and itemss can be written manually by user.
	                                                      */
}

void DAC0_setValue(uint32_t dacValue){
	DAC_SetBufferValue(DEMO_DAC_BASEADDR, 0U, dacValue);
}
