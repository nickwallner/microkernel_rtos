#include "hal.h"
#include "microkernel.h"

void flash_led(void)
{
    while (1)
    {
        GPIO_Write(GPIOA, GPIO_PIN5, GPIO_PIN_SET);
    
        mk_waitTask(mk_getCurrentTaskID(), 80);
    
        GPIO_Write(GPIOA, GPIO_PIN5, GPIO_PIN_RESET);

        mk_waitTask(mk_getCurrentTaskID(), 1000);
    }
}

void transmit_uart1(void)
{
    while (1)
    {
        USART_Transmit(USART2, "in uart task 1\r\n", 17);
        mk_waitTask(mk_getCurrentTaskID(), 1000);
    }
}

void transmit_uart2(void)
{
    while (1)
    {
        USART_Transmit(USART2, "in uart task 2\r\n", 17);
        mk_waitTask(mk_getCurrentTaskID(), 2000);
    }
}

void transmit_uart3(void)
{
    while (1)
    {
        USART_Transmit(USART2, "in uart task 3\r\n", 17);
        mk_waitTask(mk_getCurrentTaskID(), 3000);
    }
}

void transmit_uart4(void)
{
    while (1)
    {
        USART_Transmit(USART2, "in uart task 4\r\n", 17);
        mk_waitTask(mk_getCurrentTaskID(), 4000);
    }
}

void transmit_uart5(void)
{
    while (1)
    {
        USART_Transmit(USART2, "in uart task 5\r\n", 17);
        mk_waitTask(mk_getCurrentTaskID(), 5000);
    }
}

int main()
{
    /* init gpio clocks */
    GPIO_Clock_Init();

    /* LD2 is connected to PA5, so set PA5 to output mode */
    GPIO_Set_Mode(GPIOA, GPIO_PIN5, GPIO_MODE_OUTPUT);

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

    USART_Transmit(USART2, "starting kernel...\r\n", 21);

    mk_initKernel();

    mk_createTask(flash_led, NULL, 256, 0);
    mk_createTask(transmit_uart1, NULL, 256, 0);
    mk_createTask(transmit_uart2, NULL, 256, 0);
    mk_createTask(transmit_uart3, NULL, 256, 0);
    mk_createTask(transmit_uart4, NULL, 256, 0);
    mk_createTask(transmit_uart5, NULL, 256, 0);

    mk_startKernel();
}
