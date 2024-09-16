#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include "I2C.h"
#define F_CPU 1000000UL
#define TC74_W 0b10011010  // Write mode address
#define TC74_R 0b10011011  // Read mode address
#include <stdio.h>

int main(void) {
	UART_init();
	UART_sendString("Hello \r\n");
	_delay_ms(500);
	I2C_Init();

	
	_delay_ms(100);
	
	char buffer[20];


	
	while(1){
		// Set pointer to config register
		I2C_Start(TC74_W);
		I2C_Send(0x00);     // Register address 0x01 (cinfig register)
		


		I2C_Repeated_Start(TC74_R);

		uint8_t Temp = I2C_read_nack(); // Read temperature data with NACK

		I2C_Stop();
		_delay_ms(400);
		



		// Format temperature data and send over UART
		sprintf(buffer, "Temp: %d C\r\n", Temp);
		UART_sendString(buffer);

		_delay_ms(1000);

	}
	
	return 0;
}
