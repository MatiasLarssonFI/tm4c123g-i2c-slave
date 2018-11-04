#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#include "bsp.h"
#include "tm4c_cmsis.h"


int main() {
    SYSCTL->RCGC2 |= (1U << 5); // enable clock for GPIOF
    SYSCTL->GPIOHSCTL |= (1U << 5); // enable AHB for GPIOF
    
    GPIOF_HS->DIR |= (LED_RED | LED_BLUE | LED_GREEN); // set led pins as outputs
    GPIOF_HS->DEN |= (LED_RED | LED_BLUE | LED_GREEN); // digital enable
    
    // enable I2C module 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
 
    // reset module
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);
     
    // enable GPIOA peripheral that contains I2C 1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
 
    // Configure the pin muxing for I2C1 functions on port A6 and A7.
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);
     
    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
    
    // slave
    I2CSlaveInit(I2C1_BASE, 0x60U);
    I2CSlaveIntEnable(I2C1_BASE);
    
    // register interrupt handler
    I2CIntRegister(I2C1_BASE, I2C1_IRQHandler_Driverlib);
    
    while (1)
        ;
    //return 0;
}
