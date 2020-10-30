/**
 * @file    sw07.c
 * @brief   Solution to homework SW07.
 */

/* Bericht SW07:
 *
 * Die memory Funktionen habe ich verstanden. Endlich weiss ich auch was heap bedeutet,
 * das war schon lange ein Raetsel für mich.
 * Das Programm funktioniert grundsaetzlich. Auf den Median habe ich verzichtet, da
 * ich schon lange genug mit dem Programmieren der Datenauswertung beschaeftigt war.
 * Eine klare Verbesserung waere noch einige Elemente zwischenzuspeichern und nur
 * alle x Elemente tatsaechlich in den Heap zu speichern.
 * Damit wuerde verhindert, dass es zu Fragmentierung kommt.
 *
 */


#include "board.h"
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Settings
static const uint16_t PollingRateMs = 50; // after x ms a new measurement value is saved
// Graphic settings
static const uint16_t MaxChars = 100;

typedef uint32_t data_t[];

int main(void) {

	init();

	while (true) { /* run forever */

		uint32_t now = 0;
		uint32_t countMeasurement  = 0;   // number of measurements made
		data_t *pointer = NULL;           // pointer to measurement data in heap

		while (!getSW1())   /* wait until SW1 is activated */
			;

		printf("start measurement\n");
		while (getSW1()) { /* as long as SW is activated */

			/* measure if the measuring time is reached */
			if (msTicks >= (now + PollingRateMs)) {
				now = msTicks;  // save time

				/* measure brightness */
				ADC1_Start();  // start conversion
				while (!ADC1_GetStatus())	// wait until conversion is done
					;
				uint32_t value = ADC1_GetValue();  // get ADC value

				/* reallocate memory (or allocate if the pointer is NULL)*/
				pointer = (data_t*) realloc(pointer, (sizeof(uint32_t)*(countMeasurement+1)));
				if(pointer == NULL){  /* check if there is storage left */
					printf("Storage full! Value was discarded.\n");
					break;  // exit loop
				}

				(*pointer)[countMeasurement++] = value;
			}
		}   // end measurement

		printf("measurement ended\n");

		/* Calculate statistics */
		uint32_t max = 0, min = UINT32_MAX, avg = 0;
		uint64_t sum = 0;

		for(size_t i=0; i<countMeasurement; i++){  // calculate maximum
			if((*pointer)[i] > max){
				max = (*pointer)[i];
			}
		}
		for(size_t i=0; i<countMeasurement; i++){  // calculate minimum
			if((*pointer)[i] < min){
				min = (*pointer)[i];
			}
		}
		for(size_t i=0; i<countMeasurement; i++){  // calculate average
			sum += (*pointer)[i];
		}
		avg = sum/countMeasurement;

		/* show result */
		printf("numerical results:\n");
		printf("minimum: %i, average: %i, maximum: %i\n", min, avg, max);
		printf("Num of measurements: %i, Sum: %i\n", countMeasurement, sum);

		/* calculating graphical result */
		uint16_t maxRows = 200;
		uint32_t valuesPerBar = 1; // default 1 value
		if(countMeasurement > maxRows){ // more than 200 measurements
			valuesPerBar = countMeasurement / maxRows;
		}
		else{  // less than 200 measurements
			maxRows = countMeasurement;
		}

		uint32_t rows[200] = { 0 };  // all elements 0
		uint32_t largestRow = 0;
		for(uint16_t row = 0; row < maxRows; row++){  // iterate through row
			uint32_t sumBar = 0;
			for(uint16_t valueCount = 0; valueCount < valuesPerBar; valueCount++){ // calculate sum of this bar
				sumBar += (*pointer)[(row*valuesPerBar)+valueCount];
			}
			rows[row] = sumBar/valuesPerBar;  // calculate average of the sum
			if(rows[row] > largestRow){   // remember maximum row
				largestRow = rows[row];
			}
		}

		/* show result */
		printf("graphical result:\n");
		for(uint16_t row = 0; row < maxRows; row++){
			// scale this value to the largest row
			printf("\n%*c|", (MaxChars * rows[row]) / largestRow, ' ');
		}

		// free memory
		free(pointer);
	}

	return 0;
}
