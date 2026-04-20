#ifndef RCC_H_
#define RCC_H_

#include "common.h"

/* base address for rcc peripheral */
#define RCC_PERIPH_BASE_ADDR  0x40023800

/* rcc peripheral */
/* simply a pointer to a RCC_Peripheral instance placed at the
rcc base address in memory */
#define RCC ((RCC_Peripheral *) RCC_PERIPH_BASE_ADDR)

/* rcc peripheral struct, holds all the registers for the RCC peripheral */
typedef struct
{
    volatile uint32_t CR;           // RCC clock control register
    volatile uint32_t PLLCFGR;      // RCC PLL configuration register
    volatile uint32_t CFGR;         // RCC clock configuration register
    volatile uint32_t CIR;          // RCC clock interrupt register
    volatile uint32_t AHB1RSTR;     // RCC AHB1 peripheral reset register
    volatile uint32_t AHB2RSTR;     // RCC AHB2 peripheral reset register
    volatile uint32_t AHB3RSTR;     // RCC AHB3 peripheral reset register
             uint32_t RESERVED0;    // Reserved
    volatile uint32_t APB1RSTR;     // RCC APB1 peripheral reset register
    volatile uint32_t APB2RSTR;     // RCC APB2 peripheral reset register
             uint32_t RESERVED1[2]; // Reserved
    volatile uint32_t AHB1ENR;      // RCC AHB1 peripheral clock enable register
    volatile uint32_t AHB2ENR;      // RCC AHB2 peripheral clock enable register
    volatile uint32_t AHB3ENR;      // RCC AHB3 peripheral clock enable register
             uint32_t RESERVED2;    // Reserved
    volatile uint32_t APB1ENR;      // RCC APB1 peripheral clock enable register
    volatile uint32_t APB2ENR;      // RCC APB2 peripheral clock enable register
             uint32_t RESERVED3[2]; // Reserved
    volatile uint32_t AHB1LPENR;    // RCC AHB1 peripheral clock enable in low power mode register
    volatile uint32_t AHB2LPENR;    // RCC AHB2 peripheral clock enable in low power mode register
    volatile uint32_t AHB3LPENR;    // RCC AHB3 peripheral clock enable in low power mode register
             uint32_t RESERVED4;    // Reserved
    volatile uint32_t APB1LPENR;    // RCC APB1 peripheral clock enable in low power mode register
    volatile uint32_t APB2LPENR;    // RCC APB2 peripheral clock enable in low power mode register
             uint32_t RESERVED5[2]; // Reserved
    volatile uint32_t BDCR;         // RCC Backup domain control register
    volatile uint32_t CSR;          // RCC clock control & status register
             uint32_t RESERVED6[2]; // Reserved
    volatile uint32_t SSCGR;        // RCC spread spectrum clock generation register
    volatile uint32_t PLLI2SCFGR;   // RCC PLLI2S configuration register
    volatile uint32_t PLLSAICFGR;   // RCC PLLSAI configuration register
    volatile uint32_t DCKCFGR;      // RCC Dedicated Clocks configuration register
    volatile uint32_t CKGATENR;     // RCC Clocks Gated ENable Register
    volatile uint32_t DCKCFGR2;     // RCC Dedicated Clocks configuration register 2
} RCC_Peripheral;

/**
 * @brief Enable the clock(s) for the GPIO peripheral
 * 
 */
void GPIO_Clock_Init(void);

#endif // RCC_H_