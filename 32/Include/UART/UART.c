/*
 * UART.c
 *
 * Created: 9/8/2024 9:36:15 PM
 *  Author: moham
 */ 

#include "UART.h"

// Initialize UART
void UART_init(void) {
	// Set baud rate
	UBRRH = (BAUD_PRESCALE >> 8);    // High byte
	UBRRL = BAUD_PRESCALE;           // Low byte

	UCSRB = (1 << RXEN) | (1 << TXEN); // Enable receiver and transmitter
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // 8-bit data, no parity, 1 stop bit
}

// Send data through UART
void UART_send(char data) {
	while (!(UCSRA & (1 << UDRE)));  // Wait for the buffer to be empty
	UDR = data;                      // Load data into the buffer
}

// Send a string through UART
void UART_sendString(const char *str) {
	while (*str) {
		UART_send(*str++);
	}
}