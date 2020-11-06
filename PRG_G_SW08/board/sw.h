/*
 * sw.h
 *
 *  Created on: 11 Sep 2019
 *      Author: Luca Imesch
 */

#ifndef SW_H_
#define SW_H_

#include "fsl_common.h"

/* Configure Switch Inputs */
void SW_Init();

/*
 * Get Switch State
 *
 * @retval true if pressed
 */
bool getSW1();
bool getSW2();
bool getSW3();
bool getSW4();

#endif /* SW_H_ */
