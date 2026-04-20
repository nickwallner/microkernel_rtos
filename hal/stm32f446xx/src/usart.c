#include "usart.h"

/* these macros are taken verbatim from the STM32F4xx HAL */
/* they are used to calculate the value for a usart baud rate register
given the system clock frequency (_PCLK_) and desired baud rate (_BAUD_) */
/* the only macro that should be used is UART_BRR_SAMPLING16, the other
macros are not used independently */
/* UART BRR = mantissa + overflow + fraction = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0FU) */
/* Copyright (c) 2016 STMicroelectronics */
#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_)     ((uint32_t)((((uint64_t)(_PCLK_)) * 25U) / (4U * ((uint64_t)(_BAUD_)))))

#define UART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_) (UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) / 100U)

#define UART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_) ((((UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U) + 50U) / 100U)

#define UART_BRR_SAMPLING16(_PCLK_, _BAUD_)     ((UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
                                                 (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U) + \
                                                 (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))

/* write a single byte to a usart */
static inline void write_byte(USART_Peripheral *usartx, char *byte)
{
    /* write byte to data register */
    usartx->DR = *byte;

    /* wait for bit 6 to be set in status register 
    to indicate transmission is complete */
    while ((usartx->SR & BIT(6)) == 0) {}
}

/* read a single byte from a usart into a pointer */
static inline void read_byte(USART_Peripheral *usartx, char *buf)
{
    /* check that bit 5 is set to indicate received byte
    is ready to be read */
    if (usartx->SR & BIT(5))
    {
        /* read byte into buffer */
        *buf = (char)(usartx->DR & 0xFF);
    }
}

void USART_Init(USART_InitStruct *init)
{
    IRQn_Type irqn = USART1_IRQn; // default to usart1 irqn

    if (init->usartx == USART1)
    {
        /* enable usart1 clock signal */
        SET_BIT(RCC->APB2ENR, 4);

        /* configure usart1 tx and rx gpio pins */
        GPIO_Set_Mode(USART1_GPIO_PORT, USART1_TX_PIN, GPIO_MODE_AF);
        GPIO_Set_AF(USART1_GPIO_PORT, USART1_TX_PIN, USART1_GPIO_AF);

        GPIO_Set_Mode(USART1_GPIO_PORT, USART1_RX_PIN, GPIO_MODE_AF);
        GPIO_Set_AF(USART1_GPIO_PORT, USART1_RX_PIN, USART1_GPIO_AF);

        /* set irq number for enabling interrupts */
        irqn = USART1_IRQn;
    }
    else if (init->usartx == USART2)
    {
        /* enable usart2 clock signal */
        SET_BIT(RCC->APB1ENR, 17);

        /* configure usart2 tx and rx gpio pins */
        GPIO_Set_Mode(USART2_GPIO_PORT, USART2_TX_PIN, GPIO_MODE_AF);
        GPIO_Set_AF(USART2_GPIO_PORT, USART2_TX_PIN, USART2_GPIO_AF);

        GPIO_Set_Mode(USART2_GPIO_PORT, USART2_RX_PIN, GPIO_MODE_AF);
        GPIO_Set_AF(USART2_GPIO_PORT, USART2_RX_PIN, USART2_GPIO_AF);

        /* set irq number for enabling interrupts */
        irqn = USART2_IRQn;
    }
    else if (init->usartx == USART3)
    {
        /* enable usart3 clock signal */
        SET_BIT(RCC->APB1ENR, 18);

        /* configure usart3 tx and rx gpio pins */
        GPIO_Set_Mode(USART3_GPIO_PORT, USART3_TX_PIN, GPIO_MODE_AF);
        GPIO_Set_AF(USART3_GPIO_PORT, USART3_TX_PIN, USART3_GPIO_AF);

        GPIO_Set_Mode(USART3_GPIO_PORT, USART3_RX_PIN, GPIO_MODE_AF);
        GPIO_Set_AF(USART3_GPIO_PORT, USART3_RX_PIN, USART3_GPIO_AF);

        /* set irq number for enabling interrupts */
        irqn = USART3_IRQn;
    }
    else if (init->usartx == UART4)
    {
        /* enable usart4 clock signal */
        SET_BIT(RCC->APB1ENR, 19);

        /* configure usart4 tx and rx gpio pins */
        GPIO_Set_Mode(UART4_GPIO_PORT, UART4_TX_PIN, GPIO_MODE_AF);
        GPIO_Set_AF(UART4_GPIO_PORT, UART4_TX_PIN, UART4_GPIO_AF);

        GPIO_Set_Mode(UART4_GPIO_PORT, UART4_RX_PIN, GPIO_MODE_AF);
        GPIO_Set_AF(UART4_GPIO_PORT, UART4_RX_PIN, UART4_GPIO_AF);

        /* set irq number for enabling interrupts */
        irqn = UART4_IRQn;
    }
    else if (init->usartx == UART5)
    {
        /* enable usart5 clock signal */
        SET_BIT(RCC->APB1ENR, 20);

        /* configure usart5 tx and rx gpio pins */
        GPIO_Set_Mode(UART5_TX_GPIO_PORT, UART5_TX_PIN, GPIO_MODE_AF);
        GPIO_Set_AF(UART5_TX_GPIO_PORT, UART5_TX_PIN, UART5_GPIO_AF);

        GPIO_Set_Mode(UART5_RX_GPIO_PORT, UART5_RX_PIN, GPIO_MODE_AF);
        GPIO_Set_AF(UART5_RX_GPIO_PORT, UART5_RX_PIN, UART5_GPIO_AF);

        /* set irq number for enabling interrupts */
        irqn = UART5_IRQn;
    }
    else if (init->usartx == USART6)
    {
        /* enable usart6 clock signal */
        SET_BIT(RCC->APB2ENR, 5);

        /* configure usart6 tx and rx gpio pins */
        GPIO_Set_Mode(USART6_GPIO_PORT, USART6_TX_PIN, GPIO_MODE_AF);
        GPIO_Set_AF(USART6_GPIO_PORT, USART6_TX_PIN, USART6_GPIO_AF);

        GPIO_Set_Mode(USART6_GPIO_PORT, USART6_RX_PIN, GPIO_MODE_AF);
        GPIO_Set_AF(USART6_GPIO_PORT, USART6_RX_PIN, USART6_GPIO_AF);

        /* set irq number for enabling interrupts */
        irqn = USART6_IRQn;
    }

    /* reset usart control registers */
    init->usartx->CR1 = 0;
    init->usartx->CR2 = 0;
    init->usartx->CR3 = 0;

    /* enable the usart */
    init->usartx->CR1 |= BIT(13);

    /* enable transmitter/receiver */
    if (init->transmit_en) { init->usartx->CR1 |= BIT(3); } // enable transmitter
    if (init->receive_en)  { init->usartx->CR1 |= BIT(2); } // enable receiver

    /* configure interrupts */
    if (init->transmit_interrupts_en)
    {
        /* enable transmission complete interrupts */
        init->usartx->CR1 |= BIT(6);
        NVIC_EnableIRQ(irqn);
    }
    if (init->receive_interrupts_en)
    {
        /* enable data received interrupts */
        init->usartx->CR1 |= BIT(5);
        NVIC_EnableIRQ(irqn);
    }

    /* set baud rate */
    init->usartx->BRR = UART_BRR_SAMPLING16(init->sys_freq, init->baud_rate);
}

void USART_Transmit(USART_Peripheral *usartx, char *buf, size_t len)
{
    /* wait for the transmit data register to become empty */
    while ((usartx->SR & BIT(7)) == 0) { }

    while (len > 0)
    {
        write_byte(usartx, buf); // write single character (byte)
        buf++; // go to next character
        len--;
    }
}

void USART_Receive(USART_Peripheral *usartx, char *buf, size_t len)
{
    UNUSED(usartx)
    UNUSED(buf)
    UNUSED(len)

    /* if recv function is needed, implement interrupt handler for
    usart data recvd interrupts, each time interrupt fires, read byte
    and store in some internal buffer, then this function just
    reads/clears the buffer */
}
