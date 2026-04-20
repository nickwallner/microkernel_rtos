#include "rcc.h"

void GPIO_Clock_Init(void)
{
    SET_BIT(RCC->AHB1ENR, 0); // GPIOA
    SET_BIT(RCC->AHB1ENR, 1); // GPIOB
    SET_BIT(RCC->AHB1ENR, 2); // GPIOC
    SET_BIT(RCC->AHB1ENR, 3); // GPIOD
    SET_BIT(RCC->AHB1ENR, 7); // GPIOH
}