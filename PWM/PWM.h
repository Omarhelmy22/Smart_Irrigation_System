/*
 * PWM.h
 *
 *  Created on: Jun 18, 2023
 *      Author: abdal
 */

#ifndef PWM_PWM_H_
#define PWM_PWM_H_

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>


void pwm_init();
void set_pwm_duty_cycle(uint8_t duty_cycle);


#endif /* PWM_PWM_H_ */
