#ifndef __BSP_H__
#define __BSP_H__

#define SYS_CLOCK_HZ 16000000U

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)


/**
 * I2C interrupt handler specifically to register with the driverlib.
 */
void I2C1_IRQHandler_Driverlib(void);

#endif // __BSP_H__