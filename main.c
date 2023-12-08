/*
 * main.c
 *
 *  Created on: Jun 18, 2023
 *      Author: abdal
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>			/* Include Delay header file */
#include "PWM/PWM.h"
#include "Lcd/Lcd.h"
#include "ADC_INT/adc.h"
#include "UART/UART.h"
// Define temperature thresholds
#define threshold    72  // degree = 35c
unsigned int x ;
float Temp_volt;
char s1[10];
unsigned short temp ;
unsigned int soil;
unsigned char val,g_flag;
#define GetBit(Reg,BitNo)       (Reg&(1<<BitNo))
void UART_sendByte(unsigned char c){


	while(!GetBit(UCSRA,UDRE));
	UDR=c;

}

unsigned char UART_rByte(void){


	while(!GetBit(UCSRA,RXC));
	return UDR;

}



void adc_init()

{
	//    Select Vref to AVCC PIN
	SET_BIT(ADMUX,REFS0);
	CLEAR_BIT(ADMUX,REFS1);

	//    select ADC prescaler
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS0);
	//    Enable ADC
	SET_BIT(ADCSRA,ADEN);

}
uint16_t adc_read(uint8_t ch)
{
	//    select the corresponding channel
	ADMUX &= 0xE0;  //to make sure that channel selection did not messed up
	ADMUX |=ch;

	SET_BIT(ADCSRA,ADSC);  //start single conversion

	while(ADCSRA &(1<<ADSC));

	return ADC;
}
void control_motor(float temp) {
	if (temp < threshold) {
		set_pwm_duty_cycle(255); // 100% duty cycle for fast speed
	}
	else {
		set_pwm_duty_cycle(64); // 25% duty cycle for Low speed
	}
}




int main() {
	//	DDRD |=(1<<PD5);
	//	PORTD^=(1<<PD5);
	//	MCUCR&=~(1<<ISC00);
	//	MCUCR|=(1<<ISC01);
	//	GICR |= (1<<INT0);
	DDRC = 0xFF ;
	PORTC=0;
	DDRA &=0b01111110;
	// Initialize LCD module
	LCD_Init();
	UCSRB = (1<<RXCIE)|(1<<RXEN);
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	UBRRH=0;
	UBRRL=103;

	LCD_Send_String("BADAWY");	/* Write string on 1st line of LCD*/


	_delay_ms(100);
	//-------------------------------pwm init-----------------------------------------
	pwm_init();
	//-------------------------------UART SENSOR--------------------------------------
	//	Uart_init(9600);

	while (1) {
		//-------------------------------SOIL SENSOR--------------------------------------
		DDRA &=0b01111110;
		adc_init();
		soil = adc_read(0);
		if(soil<500) {
			PORTC |=(1<<PC1);
			LCD_Init();
			LCD_Send_String("Pumb is ON");
			_delay_ms(100);
			PORTC &= ~(1<<PC1);
		}
		else{
			PORTC &= ~(1<<PC1);
		}
		//-------------------------------TEMP SENSOR--------------------------------------
		DDRA &=0b01111110;
		adc_init();
		Temp_volt =adc_read(7);
		temp = ( (Temp_volt * 5) /1023)*100;
		sprintf(s1, "Temp: %u", temp);
		control_motor(Temp_volt);
		LCD_Init();
		_delay_us(5);
		LCD_Send_String(s1);	 // Write string on 1st line of LCD
		_delay_ms(500);
		//-------------------------------------------------------------------------------

		g_flag=UART_rByte();

		if(g_flag=='A'){
			PORTC|=(1<<1);
		}
		else if(g_flag=='B'){
			PORTC&=~(1<<1);
		}

	}


}

/*
ISR(INT0_vect){
	cli();
	PORTD^=(1<<PD5);
	_delay_ms(1000);
	sei();
}*/
/*
ISR(USART_RXC_vect){
	LCD_Init();
	LCD_Send_String("interrr");
	_delay_ms(100);
    val = UDR ;
    switch(val) {
        case 'A':
        PORTC |= (1<<0) ;
        break;
        case 'B':
        PORTC &= ~(1<<0) ;
        break;
    }
}
 */
ISR(USART_RXC_vect){
	g_flag=UDR;
}
