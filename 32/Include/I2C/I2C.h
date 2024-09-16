/*
 * I2C.h
 *
 * Created: 9/8/2024 9:44:57 PM
 *  Author: moham
 */ 


#ifndef I2C_H_
#define I2C_H_

#define SCL 100000UL
#include <avr/io.h>
#define F_CPU 1000000UL


#define Set_Bit(REG,BIT) (REG |= (1<<BIT))
#define Clear_Bit(REG,BIT) (REG &= (~(1<<BIT)))
#define Toggle_Bit(REG,BIT) (REG ^= (1<<BIT))
#define ROR(REG,NUM) (REG = ((REG >> NUM) | (REG << (8-NUM))))
#define ROL(REG,NUM) (REG = ((REG << NUM) | (REG >> (8-NUM))))
#define Bit_Is_Set(REG,BIT) (REG & (1<<BIT))
#define Bit_Is_Clear(REG,BIT) (!(REG & (1<<BIT)))

 void I2C_Init(void);
 void I2C_Start(uint8_t address);
 void I2C_Send(uint8_t data);
 void I2C_Stop(void);
 uint8_t I2C_read_ack(void);
 uint8_t I2C_read_nack(void);
 void I2C_Repeated_Start(uint8_t address);

// 
// 
// #define I2C_START         0x08
// #define I2C_REP_START     0x10
// #define I2C_MT_SLA_W_ACK  0x18
// #define I2C_MT_SLA_R_ACK  0x40
// #define I2C_MT_DATA_ACK   0x28
// #define I2C_MR_DATA_ACK   0x50
// #define I2C_MR_DATA_NACK  0x58
// 
// 
// void I2C_Init();
// void I2C_Start();
// void I2C_Stop();
// void I2C_Write(uint8_t data);
// uint8_t I2C_Read_ACK();
// uint8_t I2C_Read_NO_ACK();
// uint8_t I2C_Status();
#endif /* I2C_H_ */