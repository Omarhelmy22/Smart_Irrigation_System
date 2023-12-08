/*
 * PWM.c
 *
 *  Created on: Jun 18, 2023
 *      Author: abdal
 */
#include"PWM.h"

#define PWM_PIN     PB3

void pwm_init() {
	 /*
	 Set fast PWM mode with non
	 inverting output
	 */
	TCCR0|=(1<<COM01)|(1<<WGM00)|(1<<WGM01);
    //TCCR1A |= (1 << WGM10) | (1 << COM1B1); // Fast PWM mode, non-inverting output on OC1A
    //TCCR1B |= (1 << WGM12) | (1 << CS11); // Fast PWM, prescaler = 8
	//select 1:1 prescaler
	TCCR0|=(1<<CS00);
    DDRB |= (1 << PWM_PIN); // Set PWM pin as output
}

// Function to set PWM duty cycle
void set_pwm_duty_cycle(uint8_t duty_cycle) {
    OCR0 = duty_cycle;
}
