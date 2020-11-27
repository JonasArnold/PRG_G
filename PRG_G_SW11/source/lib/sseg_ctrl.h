/*
 * sseg_ctrl.h
 * 	Library to control the two seven segment display on the TinyK22.
 *
 *  Created on: 02.10.2020
 *      Author: Jonas Arnold
 */

#ifndef SSEG_CTRL_H_
#define SSEG_CTRL_H_

/* Displays a character on one of the Seven Segment displays (1 or 2)
 * Implemented characters: 0-9 or A-F or "." for a dot
 * To clear the display, set "character" variable to 0xFF
 */
void setSSEGchar(uint8_t segment, char character);

/* Displays a number on the two seven segment displays.
 * number can be from 0-99.
 * To clear the displays, set number to 0xFF.
 */
void setBothSSEGnum(uint8_t number);

#endif /* SSEG_CTRL_H_ */
