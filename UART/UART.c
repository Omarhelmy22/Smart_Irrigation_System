/*
 * UART.c
 */
#include "UART.h"

void Uart_init(long BaudRate)
{
    UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE)|(1<<TXCIE);
    UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);

    UBRRL=(unsigned char)(((F_CPU)/(16*BaudRate))-1);
}

char  UART_recieve_byte(void)
{
	while((UCSRA & (1<<RXC)) ==0);

	return UDR ;


}

