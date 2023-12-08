#include<avr/io.h>
#include"adc.h"


void adc_init_int()

{
//	Select Vref to AVCC PIN
	SET_BIT(ADMUX,REFS0);
	CLEAR_BIT(ADMUX,REFS1);
//	select ADC prescaler
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS0);
//  interrupt en
	SET_BIT(ADCSRA,ADIE);
//	Enable ADC
	SET_BIT(ADCSRA,ADEN);
}

uint16_t adc_read_int(uint8_t ch)
{
//	select the corresponding channel
	ADMUX &= 0xE0;  //to make sure that channel selection did not messed up
	ADMUX |=ch;

	SET_BIT(ADCSRA,ADSC);  //start single conversion

	while(ADCSRA &(1<<ADSC));

	return ADC;
}
