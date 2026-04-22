#include "hal.h"
#include "microkernel.h"

void flash_red_led(void)
{
    int i = 1000000;

    while (1)
    {
        GPIO_Write(GPIOA, GPIO_PIN8, GPIO_PIN_SET);
    
        while (i > 0) { i--; }
        i = 1000000;
    
        GPIO_Write(GPIOA, GPIO_PIN8, GPIO_PIN_RESET);

        while (i > 0) { i--; }
        i = 1000000;
    }
}

void flash_green_led(void)
{
    int i = 1000000;

    while (1)
    {
        GPIO_Write(GPIOA, GPIO_PIN9, GPIO_PIN_SET);
    
        while (i > 0) { i--; }
        i = 1000000;
    
        GPIO_Write(GPIOA, GPIO_PIN9, GPIO_PIN_RESET);

        while (i > 0) { i--; }
        i = 1000000;
    }
}

int main()
{
    /* init gpio clocks */
    GPIO_Clock_Init();

    /* initialize GPIO pins for LEDs */
    GPIO_Set_Mode(GPIOA, GPIO_PIN8, GPIO_MODE_OUTPUT);
    GPIO_Set_Mode(GPIOA, GPIO_PIN9, GPIO_MODE_OUTPUT);

    /* initialize usart2 */
    USART_InitStruct init = {
        .usartx = USART2,
        .baud_rate = 9600,
        .sys_freq = MK_CONFIG_SYS_FREQ_HZ,
        .transmit_en = 1,
        .transmit_interrupts_en = 0,
        .receive_en = 0,
        .receive_interrupts_en = 0
    };
    USART_Init(&init);

    USART_Transmit(USART2, "Starting scheduler...\r\n", 24);

    mk_initKernel();

    mk_createTask(flash_red_led, NULL, 256, 0);
    mk_createTask(flash_green_led, NULL, 256, 0);

    mk_startKernel();
}
