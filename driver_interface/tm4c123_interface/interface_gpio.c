#include "interface_tm4c123.h"

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

uint8_t sw1init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    return INTERFACE_OK;
}

uint8_t sw1readBit(uint8_t *pLevel)
{
    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0)
    {
        *pLevel = 0;
    }
    else
    {
        *pLevel = 1;
    }

    return INTERFACE_OK;
}

uint8_t sw2init(void)
{
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0xFF;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    return INTERFACE_OK;
}

uint8_t sw2readBit(uint8_t *pLevel)
{
    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0)
    {
        *pLevel = 0;
    }
    else
    {
        *pLevel = 1;
    }

    return INTERFACE_OK;
}