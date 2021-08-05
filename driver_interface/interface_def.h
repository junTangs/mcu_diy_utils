/**
 * @file interface_def.h
 * @author Richard Tang (richard_tang_98@163.com)
 * @brief 
 * @version alpha
 * @date 2021-08-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __INTERFACE_DEF__H__
#define __INTERFACE_DEF__H__

#include <stdint.h>

#define  INTERFACE_ERROR  (1)
#define  INTERFACE_OK  (0)


struct I2C_Interface{
  uint8_t (*init)(void);
  uint8_t (*write)(uint16_t devAddr,uint16_t memAddr,uint8_t *pData,uint16_t dataSize,uint32_t timeout);
  uint8_t (*read)(uint16_t devAddr,uint16_t memAddr,uint8_t *pData,uint16_t dataSize,uint32_t timeout);
  
};

struct SPI_Interface
{
  uint8_t (*init)(void);
  uint8_t (*write)(uint8_t *pData,uint16_t dataSize);
  uint8_t (*read)(uint8_t *pData,uint16_t dataSize);
  uint8_t (*writeRead)(uint8_t *pWriteData,uint8_t *pReadData,uint16_t dataSize);
};

#define  GPIO_READ  (0)
#define  GPIO_WRITE  (1)

struct GPIO_Interface
{
  uint8_t (*init)(void);
  void (*setMode)(uint8_t mode);
  uint8_t (*writeBit)(uint8_t level);
  uint8_t (*writeByte)(uint8_t var);
  uint8_t (*writeHalfWord)(uint16_t var);
  uint8_t (*readBit)(uint8_t *pLevel);
  uint8_t (*readByte)(uint8_t *pData);
  uint8_t (*readHalfWord)(uint16_t *pData);
};

struct USART_Interface
{
  uint8_t (*init)(void);
  uint8_t (*write)(uint8_t *pData,uint16_t dataSize);
  uint8_t (*read)(uint8_t *pData,uint16_t dataSize);
};


struct ADC_Interfaces
{
  uint8_t (*init)(void);
  uint8_t (*read)(uint16_t *pData,uint8_t channel);
};

struct PWM_Interface
{
  uint8_t (*init)(void);
  uint8_t (*setDuty)(uint8_t duty,uint8_t channel);
  uint8_t (*setPeriod)(uint32_t period);
};

struct Encoder_Interface
{
  uint8_t (*init)(void);
  uint8_t (*read)(uint16_t *pData,uint8_t *dir);
};

#endif  //!__INTERFACE_DEF__H__
