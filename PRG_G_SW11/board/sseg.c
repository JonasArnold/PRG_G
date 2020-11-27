/*
 * sseg.c
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

void setSSEG1A(){
	GPIO_PortClear(GPIOB, 1U<<1);
}

void setSSEG1B(){
	GPIO_PortClear(GPIOB, 1U<<0);
}

void setSSEG1C(){
	GPIO_PortClear(GPIOB, 1U<<2);
}

void setSSEG1D(){
	GPIO_PortClear(GPIOB, 1U<<3);
}

void setSSEG1E(){
	GPIO_PortClear(GPIOB, 1U<<16);
}

void setSSEG1F(){
	GPIO_PortClear(GPIOB, 1U<<17);
}

void setSSEG1G(){
	GPIO_PortClear(GPIOB, 1U<<18);
}

void setSSEG1DP(){
	GPIO_PortClear(GPIOB, 1U<<19);
}

// **********************************

void clearSSEG1A(){
	GPIO_PortSet(GPIOB, 1U<<1);
}

void clearSSEG1B(){
	GPIO_PortSet(GPIOB, 1U<<0);
}

void clearSSEG1C(){
	GPIO_PortSet(GPIOB, 1U<<2);
}

void clearSSEG1D(){
	GPIO_PortSet(GPIOB, 1U<<3);
}

void clearSSEG1E(){
	GPIO_PortSet(GPIOB, 1U<<16);
}

void clearSSEG1F(){
	GPIO_PortSet(GPIOB, 1U<<17);
}

void clearSSEG1G(){
	GPIO_PortSet(GPIOB, 1U<<18);
}

void clearSSEG1DP(){
	GPIO_PortSet(GPIOB, 1U<<19);
}

// **********************************

void toggleSSEG1A(){
	GPIO_PortToggle(GPIOB, 1U<<1);
}

void toggleSSEG1B(){
	GPIO_PortToggle(GPIOB, 1U<<0);
}

void toggleSSEG1C(){
	GPIO_PortToggle(GPIOB, 1U<<2);
}

void toggleSSEG1D(){
	GPIO_PortToggle(GPIOB, 1U<<3);
}

void toggleSSEG1E(){
	GPIO_PortToggle(GPIOB, 1U<<16);
}

void toggleSSEG1F(){
	GPIO_PortToggle(GPIOB, 1U<<17);
}

void toggleSSEG1G(){
	GPIO_PortToggle(GPIOB, 1U<<18);
}

void toggleSSEG1DP(){
	GPIO_PortToggle(GPIOB, 1U<<19);
}

// **********************************

void setSSEG2A(){
	GPIO_PortClear(GPIOD, 1U<<0);
}

void setSSEG2B(){
	GPIO_PortClear(GPIOD, 1U<<1);
}

void setSSEG2C(){
	GPIO_PortClear(GPIOD, 1U<<2);
}

void setSSEG2D(){
	GPIO_PortClear(GPIOD, 1U<<3);
}

void setSSEG2E(){
	GPIO_PortClear(GPIOD, 1U<<4);
}

void setSSEG2F(){
	GPIO_PortClear(GPIOD, 1U<<5);
}

void setSSEG2G(){
	GPIO_PortClear(GPIOD, 1U<<6);
}

void setSSEG2DP(){
	GPIO_PortClear(GPIOD, 1U<<7);
}

// **********************************

void clearSSEG2A(){
	GPIO_PortSet(GPIOD, 1U<<0);
}

void clearSSEG2B(){
	GPIO_PortSet(GPIOD, 1U<<1);
}

void clearSSEG2C(){
	GPIO_PortSet(GPIOD, 1U<<2);
}

void clearSSEG2D(){
	GPIO_PortSet(GPIOD, 1U<<3);
}

void clearSSEG2E(){
	GPIO_PortSet(GPIOD, 1U<<4);
}

void clearSSEG2F(){
	GPIO_PortSet(GPIOD, 1U<<5);
}

void clearSSEG2G(){
	GPIO_PortSet(GPIOD, 1U<<6);
}

void clearSSEG2DP(){
	GPIO_PortSet(GPIOD, 1U<<7);
}

// **********************************

void toggleSSEG2A(){
	GPIO_PortToggle(GPIOD, 1U<<0);
}

void toggleSSEG2B(){
	GPIO_PortToggle(GPIOD, 1U<<1);
}

void toggleSSEG2C(){
	GPIO_PortToggle(GPIOD, 1U<<2);
}

void toggleSSEG2D(){
	GPIO_PortToggle(GPIOD, 1U<<3);
}

void toggleSSEG2E(){
	GPIO_PortToggle(GPIOD, 1U<<4);
}

void toggleSSEG2F(){
	GPIO_PortToggle(GPIOD, 1U<<5);
}

void toggleSSEG2G(){
	GPIO_PortToggle(GPIOD, 1U<<6);
}

void toggleSSEG2DP(){
	GPIO_PortToggle(GPIOD, 1U<<7);
}
