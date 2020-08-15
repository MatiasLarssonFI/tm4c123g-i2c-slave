/* Board Support Package */

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/i2c.h"
#include "inc/hw_memmap.h"

#include "bsp.h"
#include "tm4c_cmsis.h"

__attribute__ ((naked)) void assert_failed (char const *file, int line) {
    // TBD: damage control
    NVIC_SystemReset();
}


void I2C1_IRQHandler_Driverlib(void) {
    // byte sent to I2C1 slave specifies the led to be toggled
    const uint32_t status = I2CSlaveStatus(I2C1_BASE);
    const uint32_t data = I2CSlaveDataGet(I2C1_BASE);
    if (status & I2C_SLAVE_ACT_RREQ) {
        if (data > 0 && data < 4) {
            // toggle requested LED
            const uint8_t led = (1U << data);
            GPIOF_HS->DATA_Bits[led] ^= led;
        }
        I2CSlaveIntClear(I2C1_BASE);
    }
}
