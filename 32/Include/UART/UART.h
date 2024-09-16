/*
 * UART1.h
 *
 * Created: 9/8/2024 9:36:40 PM
 *  Author: moham
 */ 


#ifndef UART_H_
#define UART_H_
#include <avr/io.h>
#define F_CPU 1000000UL

// Define baud rate
#define BAUD 4800
#define BAUD_PRESCALE (((F_CPU / (BAUD * 16UL))) - 1)
void UART_init(void);
void UART_send(char data);
void UART_sendString(const char *str);




#endif /* UART1_H_ */