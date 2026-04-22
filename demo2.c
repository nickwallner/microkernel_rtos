#include "hal.h"
#include "microkernel.h"

void flash_red_led(void)
{
    /* PA8 = D7 */

    while (1)
    {
        GPIO_Write(GPIOA, GPIO_PIN8, GPIO_PIN_SET);
    
        mk_waitTask(mk_getCurrentTaskID(), 80);
    
        GPIO_Write(GPIOA, GPIO_PIN8, GPIO_PIN_RESET);

        mk_waitTask(mk_getCurrentTaskID(), 1000);
    }
}

void flash_green_led(void)
{
    /* PA9 = D8 */

    while (1)
    {
        GPIO_Write(GPIOA, GPIO_PIN9, GPIO_PIN_SET);
    
        mk_waitTask(mk_getCurrentTaskID(), 3000);
    
        GPIO_Write(GPIOA, GPIO_PIN9, GPIO_PIN_RESET);

        mk_waitTask(mk_getCurrentTaskID(), 3000);
    }
}

void uart_transmit(void)
{
    while (1)
    {
        USART_Transmit(USART2, "Hello, world!\r\n", 16);

        mk_waitTask(mk_getCurrentTaskID(), 2000);
    }
}

int main()
{
    /* initialize gpio clocks */
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

    mk_createTask(flash_red_led, NULL, 256, 2);
    mk_createTask(flash_green_led, NULL, 256, 2);
    mk_createTask(uart_transmit, NULL, 256, 1);

    mk_startKernel();
}
