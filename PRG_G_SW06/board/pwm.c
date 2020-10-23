/*
 * pwm.c
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

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* The Flextimer base address/channel used for board */
#define BOARD_FTM_BASEADDR FTM3
#define OUT_FTM_CHANNEL kFTM_Chnl_4
#define RED_FTM_CHANNEL kFTM_Chnl_5
#define GREEN_FTM_CHANNEL kFTM_Chnl_6
#define BLUE_FTM_CHANNEL kFTM_Chnl_7

/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

ftm_pwm_level_select_t pwmLevel = kFTM_LowTrue;

void PWM_Init(){

	volatile uint8_t redDutycycle 	= 100U;
	volatile uint8_t blueDutycycle 	= 100U;
	volatile uint8_t greenDutycycle = 100U;

    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam;

    FTM_GetDefaultConfig(&ftmInfo);
    /* Initialize FTM module */
    FTM_Init(BOARD_FTM_BASEADDR, &ftmInfo);

    /* Configure ftm params with frequency 24kHZ */
    ftmParam.chnlNumber            = RED_FTM_CHANNEL;
    ftmParam.level                 = pwmLevel;
    ftmParam.dutyCyclePercent      = redDutycycle;
    ftmParam.firstEdgeDelayPercent = 0U;

    FTM_SetupPwm(BOARD_FTM_BASEADDR, &ftmParam, 1U, kFTM_CenterAlignedPwm, 24000U, FTM_SOURCE_CLOCK);

    /* Configure ftm params with frequency 24kHZ */
    ftmParam.chnlNumber            = GREEN_FTM_CHANNEL;
    ftmParam.level                 = pwmLevel;
    ftmParam.dutyCyclePercent      = greenDutycycle;
    ftmParam.firstEdgeDelayPercent = 0U;

    FTM_SetupPwm(BOARD_FTM_BASEADDR, &ftmParam, 1U, kFTM_CenterAlignedPwm, 24000U, FTM_SOURCE_CLOCK);

    /* Configure ftm params with frequency 24kHZ */
    ftmParam.chnlNumber            = BLUE_FTM_CHANNEL;
    ftmParam.level                 = pwmLevel;
    ftmParam.dutyCyclePercent      = blueDutycycle;
    ftmParam.firstEdgeDelayPercent = 0U;

    FTM_SetupPwm(BOARD_FTM_BASEADDR, &ftmParam, 1U, kFTM_CenterAlignedPwm, 24000U, FTM_SOURCE_CLOCK);

    FTM_StartTimer(BOARD_FTM_BASEADDR, kFTM_SystemClock);
}

void PWM_SetDutycycleRed(uint8_t redDutycycle){

	/* Disable channel output before updating the dutycycle */
    FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, RED_FTM_CHANNEL, 0U);

    /* Update PWM duty cycle */
    FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR, RED_FTM_CHANNEL, kFTM_CenterAlignedPwm, (100-redDutycycle));

    /* Software trigger to update registers */
    FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR, true);

    /* Start channel output with updated dutycycle */
    FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, RED_FTM_CHANNEL, pwmLevel);
}

void PWM_SetDutycycleGreen(uint8_t greenDutycycle){

	/* Disable channel output before updating the dutycycle */
    FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, GREEN_FTM_CHANNEL, 0U);

    /* Update PWM duty cycle */
    FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR, GREEN_FTM_CHANNEL, kFTM_CenterAlignedPwm, (100-greenDutycycle));

    /* Software trigger to update registers */
    FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR, true);

    /* Start channel output with updated dutycycle */
    FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, GREEN_FTM_CHANNEL, pwmLevel);

}

void PWM_SetDutycycleBlue(uint8_t blueDutycycle){

	/* Disable channel output before updating the dutycycle */
    FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, BLUE_FTM_CHANNEL, 0U);

    /* Update PWM duty cycle */
    FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR, BLUE_FTM_CHANNEL, kFTM_CenterAlignedPwm, (100-blueDutycycle));

    /* Software trigger to update registers */
    FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR, true);

    /* Start channel output with updated dutycycle */
    FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, BLUE_FTM_CHANNEL, pwmLevel);

}

