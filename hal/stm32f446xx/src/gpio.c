#include "gpio.h"

/* check if a GPIO pinno is set to a specific mode */
#define IS_MODE(pin, mode) ((gpiox->MODER & (mode << (pin * 2))) == ((uint32_t)(mode << (pin * 2))))

void GPIO_Pin_Init(GPIO_Pin_InitStruct *init)
{
    GPIO_Set_Mode(init->gpiox, init->pin, init->pin_mode);
    GPIO_Set_OutputType(init->gpiox, init->pin, init->output_type);
    GPIO_Set_OutputSpeed(init->gpiox, init->pin, init->output_speed);
    GPIO_Set_AF(init->gpiox, init->pin, init->alternate_function);
}

void GPIO_Set_Mode(GPIO_Peripheral *gpiox, GPIO_Pin pin, GPIO_Pin_Mode mode)
{
    gpiox->MODER &= ~(3U << (pin * 2)); // clear bits before setting them
    gpiox->MODER |= (mode << (pin * 2)); // set bits to proper mode
}

void GPIO_Set_OutputType(GPIO_Peripheral *gpiox, GPIO_Pin pin, GPIO_Output_Type type)
{
    gpiox->OTYPER |= (type << pin);
}

void GPIO_Set_OutputSpeed(GPIO_Peripheral *gpiox, GPIO_Pin pin, GPIO_Output_Speed speed)
{
    gpiox->OSPEEDR &= ~(3U << (pin * 2));
    gpiox->OSPEEDR |= (speed << (pin * 2));
}

void GPIO_Set_Pull(GPIO_Peripheral *gpiox, GPIO_Pin pin, GPIO_Pull pull)
{
    gpiox->PUPDR &= ~(3U << (pin * 2));
    gpiox->PUPDR |= (pull << (pin * 2));
}

void GPIO_Set_AF(GPIO_Peripheral *gpiox, GPIO_Pin pin, GPIO_AF af)
{
    /* check if pin is already in af mode */
    if (!(IS_MODE(pin, GPIO_MODE_AF)))
    {
        /* set pin to alternate function mode */
        GPIO_Set_Mode(gpiox, pin, GPIO_MODE_AF);
    }

    /* pins 0-7 are controlled by afrl, 8-15 are controlled by afrh */
    if (pin <= 7)
    {
        gpiox->AFRL &= ~(15U << (pin * 4)); // clear bits before setting them
        gpiox->AFRL |= ((long unsigned int)af << (pin * 4));
    }
    else
    {
        gpiox->AFRH &= ~(15U << (pin * 4)); // clear bits before setting them
        gpiox->AFRH |= ((long unsigned int)af << (pin * 4));
    }
}

void GPIO_Write(GPIO_Peripheral *gpiox, GPIO_Pin pin, GPIO_Pin_State pinstate)
{
    switch (pinstate)
    {
    case GPIO_PIN_SET:
        gpiox->BSRR = BITMASK16(pin);
        break;

    case GPIO_PIN_RESET:
        gpiox->BSRR = (BITMASK32(pin) << 16);
        break;
    }
}

GPIO_Pin_State GPIO_Read(GPIO_Peripheral *gpiox, GPIO_Pin pin)
{
    /* check if pin is set */
    if (IS_BIT_SET(gpiox->IDR, pin))
    {
        return GPIO_PIN_SET;
    }
    
    return GPIO_PIN_RESET;
}

void GPIO_Toggle(GPIO_Peripheral *gpiox, GPIO_Pin pin)
{
    /* check if pin is already set */
    if (IS_BIT_SET(gpiox->ODR, pin))
    {
        /* reset pin */
        gpiox->BSRR = (BITMASK32(pin) << 16);
    }
    else
    {
        /* set pin */
        gpiox->BSRR = BITMASK16(pin);
    }
}