/*
 * dac.h
 *
 *  Created on: 13 Sep 2019
 *      Author: Luca Imesch
 */

#ifndef DAC_H_
#define DAC_H_

/* Configures DAC0 Module */
void DAC0_Init();

/*
 * Set the Output Value
 *
 * @param DAC Output Value
 */
void DAC0_setValue(uint32_t dacValue);

#endif /* DAC_H_ */
