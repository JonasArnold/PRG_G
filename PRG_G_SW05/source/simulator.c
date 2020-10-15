/*
 * simulator.c
 *
 *  Created on: 09.10.2019
 *      Author: JumpStart
 */

#include "board.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "simulator.h"

extern const uint8_t max_cars;

extern bool ml_out, il_out, ml_in, il_in;
extern color_t ml, il;

void controller(void);

#define RND ((rand() % 4) == 0)

int32_t ml_to_il, on_il, il_to_ml = 0;

void environment(void) {

	static bool ML_out_sr, ML_in_sr, IL_in_sr, IL_out_sr = false;
	static uint32_t red_il_count = 0, red_ml_count = 0;

	while (!RND || !RND) {
		/* ML_out_arr */
		if (RND && !ML_out_sr && !ml_out) {
			ML_out_sr = true;
		}
		/* ML_in_arr */
		if (RND && !ML_in_sr && !ml_in && il_to_ml > 0) {
			ML_in_sr = true;
		}
		/* IL_in_arr */
		if (RND && !IL_in_sr && !il_in && ml_to_il > 0) {
			IL_in_sr = true;
		}
		/* IL_out_arr */
		if (RND && !IL_out_sr && !il_out && on_il > 0) {
			IL_out_sr = true;
		}
		/* ML_out_dep */
		if (RND && ML_out_sr && ml == green) {
			ML_out_sr = false;
			ml_out = true;
			ml_to_il++;
		}
		/* ML_in_dep */
		if (RND && ML_in_sr) {
			ML_in_sr = false;
			ml_in = true;
			il_to_ml--;
		}
		/* IL_in_dep */
		if (RND && IL_in_sr) {
			IL_in_sr = false;
			il_in = true;
			ml_to_il--;
			on_il++;
		}
		/* IL_out_dep */
		if (RND && IL_out_sr && il == green) {
			IL_out_sr = false;
			il_out = true;
			on_il--;
			il_to_ml++;
		}
		/* CHECK ! */
		if (ml_to_il > 0 && il_to_ml > 0) {
			printf("\nFAILED : crash on bridge\n");
			goto error;
		}
		if (ml_to_il + on_il + il_to_ml > max_cars) {
			printf("\nFAILED : too many cars\n");
			goto error;
		}

		red_il_count =
				(il == red && red_ml_count < UINT32_MAX) ?
						red_il_count + 1 : 0;
		red_ml_count =
				(ml == red && red_ml_count < UINT32_MAX) ?
						red_ml_count + 1 : 0;

		if (red_il_count >= 1000) {
			printf("\nWARNING : permanently red on island is not funny\n");
			red_il_count = 0;
		}
		if (red_ml_count >= 1000) {
			printf("\nWARNING : permanently red on mainland is not funny\n");
			red_ml_count = 0;
		}
	}

	/* show activity by led */
	(il == red) ? setLED1() : clearLED1();
	(ml == red) ? setLED2() : clearLED2();

	return;

	error: {
		uint32_t i = 0;
		while (true) {
			if (getSW2()) { /* make some noise */
				DAC0_setValue(0);
				delay_us(100);
				DAC0_setValue(4095);
				delay_us(100);
			} else { /* just blink otherwise */
				if (i == 0)
					PWM_SetDutycycleBlue(100);
				if (i == 1000)
					PWM_SetDutycycleBlue(0);
				if (i >= 2000)
					i = 0;
				else
					i++;
				delay_ms(200);
			}
		}
	}
}

void show_state(char c) {
	printf("%c : %2d %c %c %c == %02d == %c %c %c \n", c, on_il,
			il_out ? '>' : ' ', il == green ? 'G' : 'R', il_in ? '<' : ' ',
			ml_to_il + il_to_ml, ml_in ? '>' : ' ', ml == green ? 'G' : 'R',
			ml_out ? '<' : ' ');
}

int main(void) {

	init();
	srand(42);

	uint64_t i = 0;
	do {
		controller();
		if (getSW1()) /* show what controller did */
			show_state('c');
		environment();
		if (getSW1()) /* show how environment reacted on that */
			show_state('e');
		i++;
		if (!getSW1() && i % 10000 == 0)
			printf("%12lld cycles passed\n", i);
	} while (true);
	return 0;
}

