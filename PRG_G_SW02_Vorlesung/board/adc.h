/*
 * adc.h
 *
 *  Created on: 11 Sep 2019
 *      Author: Luca Imesch
 */

#ifndef ADC_H_
#define ADC_H_

#include "fsl_common.h"


/* Configures ADC0 and ADC1 Modules */
void ADC0_Init();
void ADC1_Init();

/*
 * Starts a Measurement Conversion for ADC0 or ADC1
 * Once it is completed an Interrupt occurs and saves the Measured Data,
 * which can be accessed via the GetValue Functions.
 */
void ADC0_Start();
void ADC1_Start();

/*
 * Check if the Conversion is completed
 *
 * @retval true if completed
 */
bool ADC0_GetStatus();
bool ADC1_GetStatus();

/*
 * Provides the Measured Data
 *
 * @retval Measured Data
 */
uint32_t ADC0_GetValue();
uint32_t ADC1_GetValue();

#endif /* ADC_H_ */
