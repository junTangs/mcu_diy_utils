#include "interface_tm4c123.h"



struct SPI_Interface spi1;
struct ADC_Interfaces adc0;
struct I2C_Interface i2c0;
struct PWM_Interface pwm0;
struct Encoder_Interface encoder0;
struct GPIO_Interface sw1; 
struct GPIO_Interface sw2;


void interfaceInit(void)
{
//    spi1.init = spi0Init;
//    spi1.read = spi0Read;
//    spi1.write = spi0Write;
//    spi1.writeRead = spi0WriteRead;

//    adc0.init = adc0Init;
//    adc0.read = adc0Read;

   i2c0.init = i2c0Init;
   i2c0.read = i2c0Read;
   i2c0.write = i2c0Write;

   sw1.init = sw1init;
   sw1.readBit = sw1readBit;

   sw2.init = sw2init;
   sw2.readBit = sw2readBit;

//    pwm0.init = pwm0Init;
//    pwm0.setDuty = pwm0SetDuty;
//    pwm0.setPeriod = pwm0SetPeriod;


}