
#include "interface_tm4c123.h"
#include "stdbool.h"

#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

//SDA -> PB3
//SCL -> PB2

uint8_t i2c0Init(void)
{
     SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
		SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

		GPIOPinConfigure(GPIO_PB2_I2C0SCL);
		GPIOPinConfigure(GPIO_PB3_I2C0SDA);

		GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
		GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);

    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet()/4, false);

    I2CMasterEnable(I2C0_BASE);
    return INTERFACE_OK;
}



uint8_t i2c0Write(uint16_t devAddr,uint16_t memAddr,uint8_t *pData,uint16_t dataSize,uint32_t timeout)
{
   uint32_t ui32index = 0,cnt;
	//先发送在地址
	I2CMasterSlaveAddrSet(I2C0_BASE, devAddr, false);
	I2CMasterDataPut(I2C0_BASE, memAddr);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	ui32index = 0;
	while(I2CMasterBusy(I2C0_BASE))
	{
		SysCtlDelay(SysCtlClockGet()/3000000);
		ui32index++;
		if(ui32index > timeout)
		{
			i2c0Init();
			return 1;
		}		
	}
	for(cnt = 0; cnt < dataSize; cnt++)
	{
		I2CMasterDataPut(I2C0_BASE, pData[cnt]);
		I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

		ui32index = 0;
		while(I2CMasterBusy(I2C0_BASE))
		{
			SysCtlDelay(SysCtlClockGet()/3000000);
			ui32index++;
			if(ui32index > timeout)
			{
				i2c0Init();
				return 1;
			}
		}
	}
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_STOP);
	ui32index = 0;
	while(I2CMasterBusy(I2C0_BASE))
	{
		SysCtlDelay(SysCtlClockGet()/3000000);
		ui32index++;
		if(ui32index > timeout)
		{
			i2c0Init();
			return 1;
		}
	}
	while(I2CMasterBusBusy(I2C0_BASE))
	{
		if(I2CMasterErr(I2C0_BASE) != 0x00)
		{
			I2CMasterIntClear(I2C0_BASE);
			i2c0Init();
			return 2;
		}						
	}	
	return INTERFACE_OK; 
}


uint8_t i2c0Read(uint16_t devAddr,uint16_t memAddr,uint8_t *pData,uint16_t dataSize,uint32_t timeout)
{

    uint32_t ui32index = 0,cnt;
	//先发送在地址
	I2CMasterSlaveAddrSet(I2C0_BASE, devAddr, false);
	I2CMasterDataPut(I2C0_BASE, memAddr);
	I2CMasterControl(I2C0_BASE, 0x03);
	ui32index = 0;
	while(I2CMasterBusy(I2C0_BASE))
	{
		SysCtlDelay(SysCtlClockGet()/3000000);
		ui32index++;
		if(ui32index > timeout)
		{
			i2c0Init();
			return 1;
		}		
	}
	if(dataSize <= 1)
	{
		//开始读取第一个数据
		I2CMasterSlaveAddrSet(I2C0_BASE, devAddr, true);
		I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
		ui32index = 0;
		while(I2CMasterBusy(I2C0_BASE))
		{
			SysCtlDelay(SysCtlClockGet()/3000000);
			ui32index++;
			if(ui32index > timeout)
			{
				i2c0Init();
				return 1;
			}		
		}
		pData[0] = I2CMasterDataGet(I2C0_BASE);
	}
	else
	{
		//开始读取第一个数据
		I2CMasterSlaveAddrSet(I2C0_BASE, devAddr, true);
		I2CMasterControl(I2C0_BASE, 0x0b);
		ui32index = 0;
		while(I2CMasterBusy(I2C0_BASE))
		{
			SysCtlDelay(SysCtlClockGet()/3000000);
			ui32index++;
			if(ui32index > timeout)
			{
				i2c0Init();
				return 1;
			}		
		}
		pData[0] = I2CMasterDataGet(I2C0_BASE);

		//读取第2....
		if(dataSize > 2)
		{
			for(cnt = 0; cnt < dataSize-2; cnt++)
			{
				I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
				ui32index = 0;
				while(I2CMasterBusy(I2C0_BASE))
				{
					SysCtlDelay(SysCtlClockGet()/3000000);
					ui32index++;
					if(ui32index > 10000)
					{
						i2c0Init();
						return 1;
					}		
				}
				pData[1+cnt] = I2CMasterDataGet(I2C0_BASE);
			}
		}
		//读取最后一个数据
		I2CMasterControl(I2C0_BASE, 0x01);
		while(I2CMasterBusy(I2C0_BASE))
		{
			SysCtlDelay(SysCtlClockGet()/3000000);
			ui32index++;
			if(ui32index > 10000)
			{
				i2c0Init();
				return 1;
			}		
		}
		pData[dataSize-1] = I2CMasterDataGet(I2C0_BASE);

		//产生停止位,nack
		I2CMasterControl(I2C0_BASE, 0x04);
		while(I2CMasterBusy(I2C0_BASE))
		{
			SysCtlDelay(SysCtlClockGet()/3000000);
			ui32index++;
			if(ui32index > timeout)
			{
				i2c0Init();
				return 1;
			}		
		}
	}
	while(I2CMasterBusBusy(I2C0_BASE))
	{
		if(I2CMasterErr(I2C0_BASE) != 0x00)
		{
			I2CMasterIntClear(I2C0_BASE);
			i2c0Init();
			return 2;
		}						
	}
	return INTERFACE_OK; 

}