#ifndef USART_H_
#define USART_H_

#include "common.h"

/* driver dependencies */
#include "rcc.h"
#include "gpio.h"
#include "nvic.h"

/* usart peripheral base addresses */
#define USART1_BASE_ADDR 0x40011000
#define USART2_BASE_ADDR 0x40004400
#define USART3_BASE_ADDR 0x40004800
#define UART4_BASE_ADDR  0x40004C00
#define UART5_BASE_ADDR  0x40005000
#define USART6_BASE_ADDR 0x40011400

/* usart peripherals */
#define USART1 ((USART_Peripheral *) USART1_BASE_ADDR)
#define USART2 ((USART_Peripheral *) USART2_BASE_ADDR)
#define USART3 ((USART_Peripheral *) USART3_BASE_ADDR)
#define UART4  ((USART_Peripheral *) UART4_BASE_ADDR)
#define UART5  ((USART_Peripheral *) UART5_BASE_ADDR)
#define USART6 ((USART_Peripheral *) USART6_BASE_ADDR)

/* usart peripheral registers */
typedef struct
{
    volatile uint32_t SR;   // USART status register
    volatile uint32_t DR;   // USART data register
    volatile uint32_t BRR;  // USART baud rate register
    volatile uint32_t CR1;  // USART control register 1
    volatile uint32_t CR2;  // USART control register 2
    volatile uint32_t CR3;  // USART control register 3
    volatile uint32_t GTPR; // USART guard time and prescaler register
} USART_Peripheral;

/* usart pins */
#define USART1_GPIO_PORT   GPIOA
#define USART1_GPIO_AF     GPIO_AF7
#define USART1_TX_PIN      GPIO_PIN9
#define USART1_RX_PIN      GPIO_PIN10

#define USART2_GPIO_PORT   GPIOA
#define USART2_GPIO_AF     GPIO_AF7
#define USART2_TX_PIN      GPIO_PIN2
#define USART2_RX_PIN      GPIO_PIN3

#define USART3_GPIO_PORT   GPIOB
#define USART3_GPIO_AF     GPIO_AF7
#define USART3_TX_PIN      GPIO_PIN10
#define USART3_RX_PIN      GPIO_PIN11

#define UART4_GPIO_PORT    GPIOA
#define UART4_GPIO_AF      GPIO_AF8
#define UART4_TX_PIN       GPIO_PIN0
#define UART4_RX_PIN       GPIO_PIN1

#define UART5_TX_GPIO_PORT GPIOC
#define UART5_RX_GPIO_PORT GPIOD
#define UART5_GPIO_AF      GPIO_AF8
#define UART5_TX_PIN       GPIO_PIN12 
#define UART5_RX_PIN       GPIO_PIN2

#define USART6_GPIO_PORT   GPIOC
#define USART6_GPIO_AF     GPIO_AF8
#define USART6_TX_PIN      GPIO_PIN6
#define USART6_RX_PIN      GPIO_PIN7

typedef struct
{
    USART_Peripheral *usartx;
    unsigned long     sys_freq;
    unsigned int      baud_rate;
    unsigned int      transmit_en : 1;            // enable usart transmission
    unsigned int      receive_en : 1;             // enable usart receiving
    unsigned int      transmit_interrupts_en : 1; // enable transmission complete interrupts
    unsigned int      receive_interrupts_en : 1;  // enable data received interrupts
} USART_InitStruct;

/**
 * @brief Initialize a USART peripheral
 * 
 * @param init Pointer to an initialized USART init struct
 * 
 * @details This function automatically configures the GPIO pins
 * for the UART/USART being initialized. The pins are configured
 * according to the defines in usart.h
 */
void USART_Init(USART_InitStruct *init);

/**
 * @brief Transmit data over a USART
 * 
 * @param usartx Pointer to USART peripheral
 * @param buf Pointer to buffer to transmit
 * @param len Length of buffer
 */
void USART_Transmit(USART_Peripheral *usartx, char *buf, size_t len);

/**
 * @brief Receive data from a USART
 * 
 * @param usartx Pointer to USART peripheral
 * @param buf Pointer to buffer to store data
 * @param len Length of buffer
 */
void USART_Receive(USART_Peripheral *usartx, char *buf, size_t len);

#endif // USART_H_