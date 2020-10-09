/*
 * adc.c
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
#include "fsl_adc16.h"

#define BOARD_ADC_USE_ALT_VREF

adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc0_16ChannelConfigStruct;
adc16_channel_config_t adc1_16ChannelConfigStruct;

volatile bool poti_Adc16ConversionDoneFlag = false;
volatile bool light_Adc16ConversionDoneFlag = false;
volatile uint32_t poti_Adc16ConversionValue;
volatile uint32_t light_Adc16ConversionValue;
const uint32_t g_Adc16_12bitFullRange = 4096U;

void ADC0_IRQHandler(void)
{
    poti_Adc16ConversionDoneFlag = true;

    /* Read conversion result to clear the conversion completed flag. */
    poti_Adc16ConversionValue = ADC16_GetChannelConversionValue(ADC0, 0U);

/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

void ADC1_IRQHandler(void)
{
    light_Adc16ConversionDoneFlag = true;

    /* Read conversion result to clear the conversion completed flag. */
    light_Adc16ConversionValue = ADC16_GetChannelConversionValue(ADC1, 0U);
/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

void ADC0_Init(){

	EnableIRQ(ADC0_IRQn);

	ADC16_GetDefaultConfig(&adc16ConfigStruct);

#ifdef BOARD_ADC_USE_ALT_VREF
    adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
#endif
    ADC16_Init(ADC0, &adc16ConfigStruct);
    ADC16_EnableHardwareTrigger(ADC0, false); /* Make sure the software trigger is used. */
#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    if (kStatus_Success == ADC16_DoAutoCalibration(ADC0))
    {
        //PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
    }
    else
    {
        //PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

    //PRINTF("ADC Full Range: %d\r\n", g_Adc16_12bitFullRange);
    //PRINTF("Press any key to get user channel's ADC value ...\r\n");

    adc0_16ChannelConfigStruct.channelNumber                        = 3U;
    adc0_16ChannelConfigStruct.enableInterruptOnConversionCompleted = true; /* Enable the interrupt. */
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adc0_16ChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */

}

void ADC1_Init(){

    EnableIRQ(ADC1_IRQn);

    ADC16_GetDefaultConfig(&adc16ConfigStruct);

#ifdef BOARD_ADC_USE_ALT_VREF
    adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
#endif
    ADC16_Init(ADC1, &adc16ConfigStruct);
    ADC16_EnableHardwareTrigger(ADC1, false); /* Make sure the software trigger is used. */
#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    if (kStatus_Success == ADC16_DoAutoCalibration(ADC1))
    {
        //PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
    }
    else
    {
        //PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

    //PRINTF("ADC Full Range: %d\r\n", g_Adc16_12bitFullRange);
    //PRINTF("Press any key to get user channel's ADC value ...\r\n");

    adc1_16ChannelConfigStruct.channelNumber                        = 19U;
    adc1_16ChannelConfigStruct.enableInterruptOnConversionCompleted = true; /* Enable the interrupt. */
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adc1_16ChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */

}

void ADC0_Start(){
	ADC16_SetChannelConfig(ADC0, 0U, &adc0_16ChannelConfigStruct);
	poti_Adc16ConversionDoneFlag = false;
}

void ADC1_Start(){
	ADC16_SetChannelConfig(ADC1, 0U, &adc1_16ChannelConfigStruct);
	light_Adc16ConversionDoneFlag = false;
}

bool ADC0_GetStatus(){
	return poti_Adc16ConversionDoneFlag;
}

bool ADC1_GetStatus(){
	return light_Adc16ConversionDoneFlag;
}

uint32_t ADC0_GetValue(){

	return poti_Adc16ConversionValue;
}

uint32_t ADC1_GetValue(){
	return light_Adc16ConversionValue;
}
