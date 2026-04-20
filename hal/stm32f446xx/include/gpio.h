#ifndef GPIO_H_
#define GPIO_H_

#include "common.h"

/* base address for gpio peripherals */
#define GPIO_PERIPH_BASE_ADDR 0x40020000

/* STM32F446RE i/o ports */
/* each i/o port is controlled by a corresponding GPIO peripheral
and each GPIO peripheral is 0x0400 large (aka 1024 KiB or 1 MiB) */
#define GPIOA_BASE_ADDR (GPIO_PERIPH_BASE_ADDR + 0x0000U)
#define GPIOB_BASE_ADDR (GPIO_PERIPH_BASE_ADDR + 0x0400U)
#define GPIOC_BASE_ADDR (GPIO_PERIPH_BASE_ADDR + 0x0800U)
#define GPIOD_BASE_ADDR (GPIO_PERIPH_BASE_ADDR + 0x0C00U)

/* gpio peripherals */
#define GPIOA ((GPIO_Peripheral *) GPIOA_BASE_ADDR)
#define GPIOB ((GPIO_Peripheral *) GPIOB_BASE_ADDR)
#define GPIOC ((GPIO_Peripheral *) GPIOC_BASE_ADDR)
#define GPIOD ((GPIO_Peripheral *) GPIOD_BASE_ADDR)

/* gpio peripheral struct, holds all the gpio peripheral registers */
typedef struct
{
    volatile uint32_t MODER;   // GPIO port mode register
    volatile uint32_t OTYPER;  // GPIO port output type register
    volatile uint32_t OSPEEDR; // GPIO port output speed register
    volatile uint32_t PUPDR;   // GPIO port pull-up/pull-down register
    volatile uint32_t IDR;     // GPIO port input data register
    volatile uint32_t ODR;     // GPIO port output data register
    volatile uint32_t BSRR;    // GPIO port bit set/reset register
    volatile uint32_t LCKR;    // GPIO port configuration lock register
    volatile uint32_t AFRL;    // GPIO alternate function register low
    volatile uint32_t AFRH;    // GPIO alternate function register high
} GPIO_Peripheral;

typedef enum
{
    GPIO_PIN0  = 0,
    GPIO_PIN1  = 1U,
    GPIO_PIN2  = 2U,
    GPIO_PIN3  = 3U,
    GPIO_PIN4  = 4U,
    GPIO_PIN5  = 5U,
    GPIO_PIN6  = 6U,
    GPIO_PIN7  = 7U,
    GPIO_PIN8  = 8U,
    GPIO_PIN9  = 9U,
    GPIO_PIN10 = 10U,
    GPIO_PIN11 = 11U,
    GPIO_PIN12 = 12U,
    GPIO_PIN13 = 13U,
    GPIO_PIN14 = 14U,
    GPIO_PIN15 = 15U
} GPIO_Pin;

typedef enum
{
    GPIO_AF0   = 0,
    GPIO_AF1   = 1U,
    GPIO_AF2   = 2U,
    GPIO_AF3   = 3U,
    GPIO_AF4   = 4U,
    GPIO_AF5   = 5U,
    GPIO_AF6   = 6U,
    GPIO_AF7   = 7U,
    GPIO_AF8   = 8U,
    GPIO_AF9   = 9U,
    GPIO_AF10  = 10U,
    GPIO_AF11  = 11U,
    GPIO_AF12  = 12U,
    GPIO_AF13  = 13U,
    GPIO_AF14  = 14U,
    GPIO_AF15  = 15U
} GPIO_AF;

typedef enum
{
    GPIO_PIN_RESET = 0U,
    GPIO_PIN_SET   = 1U
} GPIO_Pin_State;

typedef enum
{
    GPIO_MODE_INPUT  = 0U,
    GPIO_MODE_OUTPUT = 1U,
    GPIO_MODE_AF     = 2U,
    GPIO_MODE_ANALOG = 3U
} GPIO_Pin_Mode;

typedef enum
{
    GPIO_PUSH_PULL  = 0U,
    GPIO_OPEN_DRAIN = 1U
} GPIO_Output_Type;

typedef enum
{
    GPIO_LOW_SPEED    = 0U,
    GPIO_MEDIUM_SPEED = 1U,
    GPIO_FAST_SPEED   = 2U,
    GPIO_HIGH_SPEED   = 3U  
} GPIO_Output_Speed;

typedef enum
{
    GPIO_NO_PULL   = 0U,
    GPIO_PULL_UP   = 1U,
    GPIO_PULL_DOWN = 2U
} GPIO_Pull;

/* struct used for initializing gpio pins */
typedef struct
{
    int               pin;
    int               alternate_function;
    GPIO_Peripheral   *gpiox;
    GPIO_Pin_Mode     pin_mode;
    GPIO_Output_Type  output_type;
    GPIO_Output_Speed output_speed;
    GPIO_Pull         pull;
} GPIO_Pin_InitStruct;

/**
 * @brief Initialize a GPIO pin
 * 
 * @param gpiox Pointer to GPIO peripheral
 * @param init Pointer to filled GPIO pin init struct
 */
void GPIO_Pin_Init(GPIO_Pin_InitStruct *init);

/**
 * @brief Set the mode of a GPIO pin
 * 
 * @param gpiox Pointer to GPIO peripheral
 * @param pin Selected pin
 * @param mode Selected mode
 */
void GPIO_Set_Mode(GPIO_Peripheral *gpiox, GPIO_Pin pin, GPIO_Pin_Mode mode);

/**
 * @brief Set the output type of a GPIO pin
 * 
 * @param gpiox Pointer to GPIO peripheral
 * @param pin Selected pin
 * @param type Selected output type
 */
void GPIO_Set_OutputType(GPIO_Peripheral *gpiox, GPIO_Pin pin, GPIO_Output_Type type);

/**
 * @brief Set the output speed of a GPIO pin
 * 
 * @param gpiox Pointer to GPIO peripheral
 * @param pin Selected pin
 * @param speed Selected output speed
 */
void GPIO_Set_OutputSpeed(GPIO_Peripheral *gpiox, GPIO_Pin pin, GPIO_Output_Speed speed);

/**
 * @brief Set pull up/down for a GPIO pin
 * 
 * @param gpiox Pointer to GPIO peripheral
 * @param pin Selected pin
 * @param pull Selected pull up/down
 */
void GPIO_Set_Pull(GPIO_Peripheral *gpiox, GPIO_Pin pin, GPIO_Pull pull);

/**
 * @brief Set the alternate function of a GPIO pin
 * 
 * @param gpiox Pointer to GPIO peripheral
 * @param pin Selected pin
 * @param af Selected alternate function
 */
void GPIO_Set_AF(GPIO_Peripheral *gpiox, GPIO_Pin pin, GPIO_AF af);

/**
 * @brief Write to a GPIO pin
 * 
 * @param gpiox Pointer to GPIO peripheral
 * @param pin Selected pin
 * @param pinstate Pin state to write
 * 
 * @details This function assumes the pin passed to it
 * is already in output mode
 */
void GPIO_Write(GPIO_Peripheral *gpiox, GPIO_Pin pin, GPIO_Pin_State pinstate);

/**
 * @brief Read from a GPIO pin
 * 
 * @param gpiox Pointer to GPIO peripheral
 * @param pin Selected pin
 * @return Current state of the pin (GPIO_PIN_SET or GPIO_PIN_RESET)
 * 
 * @details This function assumes the pin passed to it
 * is already in input mode
 */
GPIO_Pin_State GPIO_Read(GPIO_Peripheral *gpiox, GPIO_Pin pin);

/**
 * @brief Toggle a GPIO pin
 * 
 * @param gpiox Pointer to GPIO peripheral
 * @param pin Selected pin
 * 
 * @details This function assumes the pin passed to it
 * is already in output mode
 */
void GPIO_Toggle(GPIO_Peripheral *gpiox, GPIO_Pin pin);

#endif // GPIO_H_