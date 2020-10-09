/**
 * @file    sw03.c
 * @brief   Solution to homework SW03.
 */


/* Bericht SW 03:
 * Fuer die Business Logik habe ich wiederum mit einer State machine gearbeitet, da ich das am uebersichtlichtsten finde.
 * Fuer die SSEG Anzeige habe ich gleich eine library geschrieben, so kann ich in zukuenftigen Anwendungen
 * diese wiederverwenden.
 * Die Implementierung verlief problemlos.
 *
 * Ablauf der Implementierung:
 * Ich habe nach dem Bottom-Up Prinzip gearbeitet. Als erstes habe ich demnach die SSEG-library implementiert.
 * Im Laufe der weiteren Implementierung hat die library einige Anpassungen erfahren.
 * Als zweites habe ich die State machine definiert, im Anschluss die States implementiert.
 * Am Schluss habe ich noch die Tastenentprellung und die Console-Ausgaben hinzugefuegt.
 * Die Tastenentprellung hatte ich anfangs ohne delay eingebaut. Es kam dann zu Fehlerkennungen des Taster-Loslassens.
 * Nach hinzufuegen des delays funktioniert alles problemlos.
 */

#include "board.h"
#include "sseg_ctrl.h"
#include <stdio.h>
#include <stdbool.h>

/* Constants */
#define GRANULARITY_MS 1   // Granularity of the delays
#define COUNTDOWN_S 10     // Countdown start value

/* State machine */
int state = 0;                 // 0 = countdown not started yet, 1 = countdown running,
                               // 2 = countdown interrupted, 3 = countdown finished

/* Variables */
int millis_counter = 0;        // counter for 1000ms
int countdownS = COUNTDOWN_S;  // seconds counter for SSEG
bool sw4Pressed = false;       // flag for when button was just pressed

/* Functions */
void soundBuzzer(int timeMs);
bool checkSw4();

/* MAIN */
int main(void) {
	init();

	while(1)  // endless
	{
		switch(state)
		{
			case 0: // countdown not started yet
				if(getSW3())  // countdown was started
				{
					state = 1;
					setBothSSEGnum(countdownS); // set first number on SSEG
					printf("Countdown was started.\n");
				}
			break;

			case 1: // countdown running
				delay_ms(GRANULARITY_MS);          // wait
				millis_counter += GRANULARITY_MS;  // add ms waited

				if(millis_counter >= 1000)   // a second has finished
				{
					countdownS--;;              // decrement 1 s
					setBothSSEGnum(countdownS); // set SSEG to seconds left
					millis_counter = 0;         // reset ms counter
				}

				if(countdownS == 0)
				{
					state = 3;  // countdown finished
					printf("Countdown finished!\n");
				}

				if(checkSw4())  // interruption?
				{
					setLED2();
					state = 2;
					printf("Countdown was interrupted.\n");
				}
			break;

			case 2: // countdown interrupted
				if(checkSw4())
				{
					state = 1; // restart countdown
					clearLED2();  // disable LED
					printf("Countdown was restarted.\n");
				}
			break;

			case 3:  // countdown finished
				soundBuzzer(3);
				setBothSSEGnum(0xFF);  // clear display
				countdownS = COUNTDOWN_S; // reset variables
				state = 0;  // next state
			break;
		}
	}

	return 0;
}

/* Generates a beeping sound on the buzzer */
void soundBuzzer(int timeMs)
{
	for (int i=0; i<(timeMs*5000); i++)
	{
		DAC0_setValue(1000);
		delay_us(100);
		DAC0_setValue(2000);
		delay_us(100);
	}
}

/* Checks if the SW4 was pressed (incl. debouncing).*/
/* Returns true if the button was pressed, false if not or still pressed */
bool checkSw4()
{
	if(getSW4() && sw4Pressed == false)  // button was pressed again
	{
		sw4Pressed = true; // set flag
		return true;
	}
	else if (!getSW4() && sw4Pressed == true)  // button was released
	{
		delay_ms(20);
		if(!getSW4())    // still not pressed?  (Debounce)
		{
			sw4Pressed = false;  // reset flag
			return false;
		}
	}
	return false;
}
