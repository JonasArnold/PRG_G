/*
 * pwm.h
 *
 *  Created on: 12 Sep 2019
 *      Author: Luca Imesch
 */

#ifndef PWM_H_
#define PWM_H_

/* Configures PWM Module */
void PWM_Init();

/*
 * Set duty cycle of the different Channels
 *
 * @param duty cycle in percent
 */
void PWM_SetDutycycleRed(uint8_t redDutycycle);
void PWM_SetDutycycleGreen(uint8_t greenDutycycle);
void PWM_SetDutycycleBlue(uint8_t blueDutycycle);


#endif /* PWM_H_ */
