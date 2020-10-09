/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v4.0
* BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********/

/**
 * @file    pin_mux.c
 * @brief   Board pins file.
 */
 
/* This is a template for board specific configuration created by MCUXpresso IDE Project Wizard.*/

#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

static const gpio_pin_config_t LED_configOutput = {
  kGPIO_DigitalOutput,  /* use as output pin */
  0,  /* initial value */
};

//static const gpio_pin_config_t SW_configInput = {
//  kGPIO_DigitalInput,  /* use as output pin */
//  0,  /* initial value */
//};

static const port_pin_config_t SW_configPullUp = {
		/* Internal pull-up resistor is enabled */
        kPORT_PullUp,
        /* Fast slew rate is configured */
        kPORT_FastSlewRate,
        /* Passive filter is disabled */
        kPORT_PassiveFilterDisable,
        /* Open drain is disabled */
        kPORT_OpenDrainDisable,
        /* Low drive strength is configured */
        kPORT_LowDriveStrength,
        /* Pin is configured as PTA1 */
        kPORT_MuxAsGpio,
        /* Pin Control Register fields [15:0] are not locked */
        kPORT_UnlockRegister
};

static const gpio_pin_config_t SevenSEG_configOutput = {
  kGPIO_DigitalOutput,  /* use as output pin */
  1,  /* initial value */
};

/**
 * @brief Set up and initialize all required blocks and functions related to the board hardware.
 */
void BOARD_InitBootPins(void) {
	/* The user initialization should be placed here */

    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);

    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    // LED 								*********************************************************************

    /* PORTA1 is configured as Digital Output */
    PORT_SetPinMux(PORTA, 1U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOA, 1U, &LED_configOutput);

    /* PORTA2 is configured as Digital Output */
    PORT_SetPinMux(PORTA, 2U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOA, 2U, &LED_configOutput);

    // Switches 						*********************************************************************

    PORT_SetPinConfig(PORTA, 4U, &SW_configPullUp);
    PORT_SetPinConfig(PORTA, 5U, &SW_configPullUp);
    PORT_SetPinConfig(PORTA, 12U, &SW_configPullUp);
    PORT_SetPinConfig(PORTA, 13U, &SW_configPullUp);

    // Tilt								*********************************************************************

    PORT_SetPinConfig(PORTE, 1U, &SW_configPullUp);

    // PWM		 						*********************************************************************

    PORT_SetPinMux(PORTC, 8U, kPORT_MuxAlt3);
    PORT_SetPinMux(PORTC, 9U, kPORT_MuxAlt3);
    PORT_SetPinMux(PORTC, 10U, kPORT_MuxAlt3);
    PORT_SetPinMux(PORTC, 11U, kPORT_MuxAlt3);

    // 7-Segment Right Position 		*********************************************************************

    /* PORTD0 is configured as Digital Output */
    PORT_SetPinMux(PORTD, 0U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOD, 0U, &SevenSEG_configOutput);

    /* PORTD1 is configured as Digital Output */
    PORT_SetPinMux(PORTD, 1U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOD, 1U, &SevenSEG_configOutput);

    /* PORTD2 is configured as Digital Output */
    PORT_SetPinMux(PORTD, 2U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOD, 2U, &SevenSEG_configOutput);

    /* PORTD3 is configured as Digital Output */
    PORT_SetPinMux(PORTD, 3U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOD, 3U, &SevenSEG_configOutput);

    /* PORTD4 is configured as Digital Output */
    PORT_SetPinMux(PORTD, 4U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOD, 4U, &SevenSEG_configOutput);

    /* PORTD5 is configured as Digital Output */
    PORT_SetPinMux(PORTD, 5U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOD, 5U, &SevenSEG_configOutput);

    /* PORTD6 is configured as Digital Output */
    PORT_SetPinMux(PORTD, 6U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOD, 6U, &SevenSEG_configOutput);

    /* PORTD7 is configured as Digital Output */
    PORT_SetPinMux(PORTD, 7U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOD, 7U, &SevenSEG_configOutput);

    // 7-Segment Left Position 		*********************************************************************

    /* PORTB0 is configured as Digital Output */
    PORT_SetPinMux(PORTB, 0U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOB, 0U, &SevenSEG_configOutput);

    /* PORTB1 is configured as Digital Output */
    PORT_SetPinMux(PORTB, 1U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOB, 1U, &SevenSEG_configOutput);

    /* PORTB2 is configured as Digital Output */
    PORT_SetPinMux(PORTB, 2U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOB, 2U, &SevenSEG_configOutput);

    /* PORTB3 is configured as Digital Output */
    PORT_SetPinMux(PORTB, 3U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOB, 3U, &SevenSEG_configOutput);

    /* PORTB16 is configured as Digital Output */
    PORT_SetPinMux(PORTB, 16U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOB, 16U, &SevenSEG_configOutput);

    /* PORTB17 is configured as Digital Output */
    PORT_SetPinMux(PORTB, 17U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOB, 17U, &SevenSEG_configOutput);

    /* PORTB18 is configured as Digital Output */
    PORT_SetPinMux(PORTB, 18U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOB, 18U, &SevenSEG_configOutput);

    /* PORTB19 is configured as Digital Output */
    PORT_SetPinMux(PORTB, 19U, kGPIO_DigitalOutput);
    GPIO_PinInit(GPIOB, 19U, &SevenSEG_configOutput);
}
