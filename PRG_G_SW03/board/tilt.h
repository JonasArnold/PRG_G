/*
 * tilt.h
 *
 *  Created on: 13 Sep 2019
 *      Author: JumpStart
 */

#ifndef TILT_H_
#define TILT_H_

/* Configure Tilt Sensor Input */
void TILT_Init();

/*
 * Get Tilt Sensor State
 *
 * @retval true if tilted
 */
bool getTilt();


#endif /* TILT_H_ */
