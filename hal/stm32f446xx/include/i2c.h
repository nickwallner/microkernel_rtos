#ifndef I2C_H_
#define I2C_H_

#include "common.h"

/* driver dependencies */
#include "rcc.h"
#include "gpio.h"

/* base address for i2c peripherals */
#define I2C_PERIPH_BASE_ADDR 0x40005400

/* i2c peripheral addresses */
#define I2C1_BASE_ADDR (I2C_PERIPH_BASE_ADDR + 0x0000U)
#define I2C2_BASE_ADDR (I2C_PERIPH_BASE_ADDR + 0x0400U)
#define I2C3_BASE_ADDR (I2C_PERIPH_BASE_ADDR + 0x0800U)

/* i2c peripherals */
#define I2C1 ((I2C_Peripheral *) I2C1_BASE_ADDR)
#define I2C2 ((I2C_Peripheral *) I2C2_BASE_ADDR)
#define I2C3 ((I2C_Peripheral *) I2C3_BASE_ADDR)

/* i2c peripheral registers */
typedef struct
{
    volatile uint32_t CR1;   // I2C control register 1
    volatile uint32_t CR2;   // I2C control register 2
    volatile uint32_t OAR1;  // I2C own address register 1
    volatile uint32_t OAR2;  // I2C own address register 2
    volatile uint32_t DR;    // I2C data register
    volatile uint32_t SR1;   // I2C status register 1
    volatile uint32_t SR2;   // I2C status register 2
    volatile uint32_t CCR;   // I2C clock control register
    volatile uint32_t TRISE; // I2C TRISE (rise time) register
    volatile uint32_t FLTR;  // I2C filter register
} I2C_Peripheral;

/* i2c gpio pins */
#define I2C1_GPIO_PORT GPIOB
#define I2C1_GPIO_AF   GPIO_AF4
#define I2C1_SDA_PIN   GPIO_PIN7
#define I2C1_SCL_PIN   GPIO_PIN6

#define I2C2_GPIO_PORT GPIOB
#define I2C2_GPIO_AF   GPIO_AF4
#define I2C2_SDA_PIN   GPIO_PIN9
#define I2C2_SCL_PIN   GPIO_PIN8

#define I2C3_SDA_GPIO_PORT GPIOB
#define I2C3_SCL_GPIO_PORT GPIOA
#define I2C3_GPIO_AF       GPIO_AF4
#define I2C3_SDA_PIN       GPIO_PIN4
#define I2C3_SCL_PIN       GPIO_PIN8

/* I'm really not sure if its beneficial to have these initializer "functions"
written as macros... I guess I just wanted to try something new :) */
#define I2C1_GPIO_Pin_Init() do { \
    GPIO_Pin_InitStruct I2C1_GPIO_SDA_Pin_Initializer = { \
        .pin = I2C1_SDA_PIN, \
        .alternate_function = I2C1_GPIO_AF, \
        .gpiox = I2C1_GPIO_PORT, \
        .pin_mode = GPIO_MODE_AF, \
        .output_type = GPIO_OPEN_DRAIN, \
        .output_speed = GPIO_FAST_SPEED, \
        .pull = GPIO_PULL_UP \
    }; \
    GPIO_Pin_InitStruct I2C1_GPIO_SCL_Pin_Initializer = { \
        .pin = I2C1_SCL_PIN, \
        .alternate_function = I2C1_GPIO_AF, \
        .gpiox = I2C1_GPIO_PORT, \
        .pin_mode = GPIO_MODE_AF, \
        .output_type = GPIO_OPEN_DRAIN, \
        .output_speed = GPIO_FAST_SPEED, \
        .pull = GPIO_PULL_UP \
    }; \
    GPIO_Pin_Init(&I2C1_GPIO_SDA_Pin_Initializer); \
    GPIO_Pin_Init(&I2C1_GPIO_SCL_Pin_Initializer); \
} while(0)

#define I2C2_GPIO_Pin_Init() do { \
    GPIO_Pin_InitStruct I2C2_GPIO_SDA_Pin_Initializer = { \
        .pin = I2C2_SDA_PIN, \
        .alternate_function = I2C2_GPIO_AF, \
        .gpiox = I2C2_GPIO_PORT, \
        .pin_mode = GPIO_MODE_AF, \
        .output_type = GPIO_OPEN_DRAIN, \
        .output_speed = GPIO_FAST_SPEED, \
        .pull = GPIO_PULL_UP \
    }; \
    GPIO_Pin_InitStruct I2C2_GPIO_SCL_Pin_Initializer = { \
        .pin = I2C2_SCL_PIN, \
        .alternate_function = I2C2_GPIO_AF, \
        .gpiox = I2C2_GPIO_PORT, \
        .pin_mode = GPIO_MODE_AF, \
        .output_type = GPIO_OPEN_DRAIN, \
        .output_speed = GPIO_FAST_SPEED, \
        .pull = GPIO_PULL_UP \
    }; \
    GPIO_Pin_Init(&I2C2_GPIO_SDA_Pin_Initializer); \
    GPIO_Pin_Init(&I2C2_GPIO_SCL_Pin_Initializer); \
} while(0)

#define I2C3_GPIO_Pin_Init() do { \
    GPIO_Pin_InitStruct I2C3_GPIO_SDA_Pin_Initializer = { \
        .pin = I2C3_SDA_PIN, \
        .alternate_function = I2C3_GPIO_AF, \
        .gpiox = I2C3_SDA_GPIO_PORT, \
        .pin_mode = GPIO_MODE_AF, \
        .output_type = GPIO_OPEN_DRAIN, \
        .output_speed = GPIO_FAST_SPEED, \
        .pull = GPIO_PULL_UP \
    }; \
    GPIO_Pin_InitStruct I2C3_GPIO_SCL_Pin_Initializer = { \
        .pin = I2C3_SCL_PIN, \
        .alternate_function = I2C3_GPIO_AF, \
        .gpiox = I2C3_SCL_PIO_PORT, \
        .pin_mode = GPIO_MODE_AF, \
        .output_type = GPIO_OPEN_DRAIN, \
        .output_speed = GPIO_FAST_SPEED, \
        .pull = GPIO_PULL_UP \
    }; \
    GPIO_Pin_Init(&I2C3_GPIO_SDA_Pin_Initializer); \
    GPIO_Pin_Init(&I2C3_GPIO_SCL_Pin_Initializer); \
} while(0)

void I2C_Init(I2C_Peripheral *);

#endif // I2C_H_
