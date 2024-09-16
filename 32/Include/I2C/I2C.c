 #include "I2C.h"

void I2C_Init(void){
	TWBR = (uint8_t)((F_CPU/SCL - 16) / 2); // Set bit rate register
	TWCR = (1<<TWEN);
	TWSR = 0x00;

}

void I2C_Start(uint8_t address){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	uint8_t status = TWSR & 0xF8;
	if (status != 0x08) {
		return ; // Start condition not transmitted
	}
	TWDR = address;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	status = TWSR & 0xF8;
	if (status != 0x18 && status != 0x40) {
		return ; // Address not acknowledged
	}
}

void I2C_Stop(void){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while (TWCR & (1<<TWSTO)); // Wait until stop condition is executed
}

void I2C_Send(uint8_t data){
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	uint8_t status = TWSR & 0xF8;
	if (status != 0x28) {
		return ; // Data not acknowledged
	}
}

uint8_t I2C_read_ack(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);  // ACK Enable
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t I2C_read_nack(void){
	TWCR = (1 << TWINT) | (1 << TWEN);  // NACK Enable
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

void I2C_Repeated_Start(uint8_t address){
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	uint8_t status = TWSR & 0xF8;
	if (status != 0x10) {
		return; // Repeated start condition not transmitted
	}
	TWDR = address;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	status = TWSR & 0xF8;
	if (status != 0x18 && status != 0x40) {
		return; // Address not acknowledged
	}
}

// 
// void I2C_Init()
// {
// 	TWBR = 0x02;
// 	TWCR = (1<<TWEN);
// 	TWSR = 0x00;
// 	TWAR = 0b00000010;
// }
// 
// void I2C_Start()
// {
// 	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
// 	while(Bit_Is_Clear(TWCR,TWINT));
// }
// 
// void I2C_Stop()
// {
// 	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
// }
// 
// void I2C_Write(uint8_t data)
// {
// 	TWDR = data;
// 	TWCR = (1<<TWINT)|(1<<TWEN);
// 	while(Bit_Is_Clear(TWCR,TWINT));
// }
// 
// uint8_t I2C_Read_ACK()
// {
// 	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
// 	while(Bit_Is_Clear(TWCR,TWINT));
// 	return TWDR;
// }
// 
// uint8_t I2C_Read_NO_ACK()
// {
// 	TWCR = (1<<TWINT)|(1<<TWEN);
// 	while(Bit_Is_Clear(TWCR,TWINT));
// 	return TWDR;
// }
// 
// uint8_t I2C_Status()
// {
// 	uint8_t status;
// 	status = (TWSR & 0xF8);
// 	return status;
// }