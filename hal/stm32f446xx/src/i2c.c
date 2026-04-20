#include "i2c.h"

void I2C_Init(I2C_Peripheral *i2cx)
{
    if (i2cx == I2C1)
    {
        /* enable clock */
        SET_BIT(RCC->APB1ENR, 21);

        /* configure gpio pins */
        I2C1_GPIO_Pin_Init();

        // TODO: are there any helpful macros from the stm32 hal for setting these registers?

        /* set apb1 bus operating frequency (16mhz) */
        /* default HSI clock freq is 16mhz */
        i2cx->CR2 |= 0b010000;
        
        /* set clock control register and rise time register */
        /* these values are calculated for a target i2c freq of 100khz */
        /* CCR = PCLK / (2 * i2c_target_freq) */
        /* TRISE = (PCLK / 1,000,000) + 1 */
        /* for now, these values are hardcoded just so that I can test
        the rest of the i2c driver */
        i2cx->CCR |= 80U;
        i2cx->TRISE |= 17U;

        /* enable the peripheral */
        SET_BIT(i2cx->CR1, 0);
    }
}