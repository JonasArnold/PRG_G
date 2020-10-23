/**
 * @file    sw06.c
 * @brief   Solution to homework SW06.
 */

/*
 * Bericht SW06:
 *
 * Die Implementation lief gut. Das Programm laeuft wie es soll.
 * Den Tipp bezgl. vergleichen der Files fand ich sehr hilfreich.
 * Ich habe vieles ueber enums und structs gelernt. Das ist sicherlich hilfreich fuer weitere Projekte.
 *
 * Zeitlich habe ich ca. 30min ausserhalb des Laborunterrichts investiert.
 */

#include "board.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
	red, orange, yellow, green, turquoise, blue
} color;

typedef enum {
    none, low, medium, high
} level_t;

typedef enum {
	F, E, D, C, B, A
} intensity_t;

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} rgb_t;

rgb_t colors[6] = {
		[red]={.red = 100, .green = 0, .blue = 0},
		[orange]={.red = 100, .green = 10, .blue = 0},
		[yellow]={.red = 100, .green = 30, .blue = 0},
		[green]={.red = 0, .green = 100, .blue = 0},
		[turquoise]={.red = 0, .green = 100, .blue = 80},
		[blue]={.red = 0, .green = 0, .blue = 100}
};


int main(void) {

	init();

	uint32_t marker = msTicks;
	uint8_t cycleCounter = 0;
	level_t prevLevels[10] = {none, none, none, none, none, none, none, none, none, none};

	while (true) {

		bool lastTiltState = getTilt();
		uint16_t activationCounter = 0;

		/* Record activations for 1 second */
		activationCounter = 0;   // reset activation counter
		while (msTicks < marker + 1000)	{
			/* tilt state changed */
			if(getTilt() != lastTiltState)
			{
				lastTiltState = !lastTiltState;  // invert state
				activationCounter++;
			}
		}
		printf("Time %6d [ms], Activations: %4d ", msTicks, activationCounter);
		marker += 1000;

		// Rate Level of Activations
		level_t currentLevel;
		if(activationCounter <= 0 && activationCounter <= 9){
			currentLevel = none;
		}
		else if(activationCounter >= 10 && activationCounter <= 99){
			currentLevel = low;
		}
		else if(activationCounter >= 100 && activationCounter <= 199){
			currentLevel = medium;
		}
		else if(activationCounter >= 200 && activationCounter <= sizeof(activationCounter)){
			currentLevel = high;
		}
		// save intensity for evaluation later
		prevLevels[cycleCounter++] = currentLevel;
		if(cycleCounter >= 10)
		{
			cycleCounter = 0;  // set counter to 0 again (start from beginning)
		}

		// Evaluation of intensity
		uint8_t secondsPerLevel[4] = {0, 0, 0, 0};
		for(uint8_t i = 0; i < sizeof(prevLevels)/sizeof(prevLevels[0]); i ++)
		{
			// count number of seconds the intensity was active
			secondsPerLevel[prevLevels[i]]++;
		}

		// get current intensity for LED
		intensity_t currentIntensity = F;
		if(secondsPerLevel[low] >= 3){
			currentIntensity = E;
		}
		if(secondsPerLevel[low] >= 6){
			currentIntensity = D;
		}
		if(secondsPerLevel[medium] >= 3){
			currentIntensity = C;
		}
		if(secondsPerLevel[medium] >= 6){
			currentIntensity = B;
		}
		if(secondsPerLevel[high] >= 6){
			currentIntensity = A;
		}

		printf("2s Level: %i, 10s Intensity: %i\n", currentLevel, currentIntensity);

		// set intensity to LED
		rgb_t currentColor = colors[currentIntensity];
		PWM_SetDutycycleRed(currentColor.red);
		PWM_SetDutycycleGreen(currentColor.green);
		PWM_SetDutycycleBlue(currentColor.blue);
	}

	return 0;
}


