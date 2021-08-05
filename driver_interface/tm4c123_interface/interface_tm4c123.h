#ifndef __INTERFACE__H__
#define __INTERFACE__H__
#include "interface_def.h"
// hardware include 

extern struct SPI_Interface spi1;
extern struct ADC_Interfaces adc0;
extern struct I2C_Interface i2c0;
extern struct PWM_Interface pwm0;
extern struct Encoder_Interface encoder0;

extern struct GPIO_Interface sw1;
extern struct GPIO_Interface sw2;

extern uint8_t sw1init(void);
extern uint8_t sw1readBit(uint8_t *pLevel);

extern uint8_t sw2init(void);
extern uint8_t sw2readBit(uint8_t *pLevel);


extern uint8_t spi0Init(void);
extern uint8_t spi0Write(uint8_t *pData,uint16_t dataSize);
extern uint8_t spi0Read(uint8_t *pData,uint16_t dataSize);
extern uint8_t spi0WriteRead(uint8_t *pWriteData,uint8_t *pReadData,uint16_t dataSize);

extern uint8_t adc0Init(void);
extern uint8_t adc0Read(uint16_t *pData,uint8_t channel);


extern uint8_t usart1Init(void);
extern uint8_t usart1Write(uint8_t *pData,uint16_t dataSize);
extern uint8_t suart1Read(uint8_t *pData,uint16_t dataSize);

extern uint8_t i2c0Init(void);
extern uint8_t i2c0Write(uint16_t devAddr,uint16_t memAddr,uint8_t *pData,uint16_t dataSize,uint32_t timeout);
extern uint8_t i2c0Read(uint16_t devAddr,uint16_t memAddr,uint8_t *pData,uint16_t dataSize,uint32_t timeout);

extern uint8_t pwm0Init(void);
extern uint8_t pwm0SetDuty(uint8_t duty,uint8_t channel);
extern uint8_t pwm0SetPeriod(uint32_t period);

// user interface define 

void interfaceInit(void);

#endif  //!__INTERFACE__H__
