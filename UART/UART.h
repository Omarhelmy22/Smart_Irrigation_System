/*
 * UART.h
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
//#define  F_CPU 16000000UL

void Uart_init(long BaudRate);
char UART_recieve_byte(void);

#endif /* UART_H_ */
