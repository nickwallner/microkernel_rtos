/****************************************************************** */
/* STARTUP CODE FOR STM32F446RE                                     */
/*                                                                  */
/* This code defines the vector table for the MCU and               */
/* also the Reset_Handler, which is responsible for initializing    */
/* the MCU's SRAM using symbols defined in the linker script        */
/* prior to executing all other code.                               */
/*                                                                  */
/****************************************************************** */

/* assume main() is defined somewhere */
extern int main();

/* initial stack pointer symbol defined in the linker script */
extern unsigned long _estack;

/* reset handler is the very first function executed when the
mcu is is reset */
__attribute__((noreturn)) void Reset_Handler(void)
{
    /* linker section symbols, they are defined in the linker script */
    extern long _sdata;
    extern long _edata;
    extern long _sidata;
    extern long _sbss;
    extern long _ebss;

    /* copy .data section to RAM */
    for (long *dest = &_sdata, *src = &_sidata; dest < &_edata;)
    {
        *dest++ = *src++;
    }

    /* zero-initialize .bss section */
    for (long *dest = &_sbss; dest < &_ebss; dest++)
    {
        *dest = 0;
    }

    main(); // enter main after initializing memory

    while(1) {} // infinite loop if main returns
}

/* weak declarations for cortex-m4 processor exception handlers */
__attribute__((weak, alias("Default_Handler"))) void NMI_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void HardFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void MemManage_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void BusFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void UsageFault_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SVC_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void DebugMon_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void PendSV_Handler(void);
__attribute__((weak, alias("Default_Handler"))) void SysTick_Handler(void);

/* weak declarations for stm32f446xx interrupts */
/* the names for each handler are consistent with the names used
in the stm32f446 user reference manual */
__attribute__((weak, alias("Default_Handler"))) void WWDG_IRQHandler(void);               /* Window WatchDog                             */
__attribute__((weak, alias("Default_Handler"))) void PVD_IRQHandler(void);                /* PVD through EXTI Line detection             */
__attribute__((weak, alias("Default_Handler"))) void TAMP_STAMP_IRQHandler(void);         /* Tamper and TimeStamps through the EXTI line */
__attribute__((weak, alias("Default_Handler"))) void RTC_WKUP_IRQHandler(void);           /* RTC Wakeup through the EXTI line            */
__attribute__((weak, alias("Default_Handler"))) void FLASH_IRQHandler(void);              /* FLASH                                       */
__attribute__((weak, alias("Default_Handler"))) void RCC_IRQHandler(void);                /* RCC                                         */
__attribute__((weak, alias("Default_Handler"))) void EXTI0_IRQHandler(void);              /* EXTI Line0                                  */
__attribute__((weak, alias("Default_Handler"))) void EXTI1_IRQHandler(void);              /* EXTI Line1                                  */
__attribute__((weak, alias("Default_Handler"))) void EXTI2_IRQHandler(void);              /* EXTI Line2                                  */
__attribute__((weak, alias("Default_Handler"))) void EXTI3_IRQHandler(void);              /* EXTI Line3                                  */
__attribute__((weak, alias("Default_Handler"))) void EXTI4_IRQHandler(void);              /* EXTI Line4                                  */
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream0_IRQHandler(void);       /* DMA1 Stream 0                               */
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream1_IRQHandler(void);       /* DMA1 Stream 1                               */
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream2_IRQHandler(void);       /* DMA1 Stream 2                               */
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream3_IRQHandler(void);       /* DMA1 Stream 3                               */
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream4_IRQHandler(void);       /* DMA1 Stream 4                               */
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream5_IRQHandler(void);       /* DMA1 Stream 5                               */
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream6_IRQHandler(void);       /* DMA1 Stream 6                               */
__attribute__((weak, alias("Default_Handler"))) void ADC_IRQHandler(void);                /* ADC1, ADC2 and ADC3s                        */
__attribute__((weak, alias("Default_Handler"))) void CAN1_TX_IRQHandler(void);            /* CAN1 TX                                     */
__attribute__((weak, alias("Default_Handler"))) void CAN1_RX0_IRQHandler(void);           /* CAN1 RX0                                    */
__attribute__((weak, alias("Default_Handler"))) void CAN1_RX1_IRQHandler(void);           /* CAN1 RX1                                    */
__attribute__((weak, alias("Default_Handler"))) void CAN1_SCE_IRQHandler(void);           /* CAN1 SCE                                    */
__attribute__((weak, alias("Default_Handler"))) void EXTI9_5_IRQHandler(void);            /* External Line[9:5]s                         */
__attribute__((weak, alias("Default_Handler"))) void TIM1_BRK_TIM9_IRQHandler(void);      /* TIM1 Break and TIM9                         */
__attribute__((weak, alias("Default_Handler"))) void TIM1_UP_TIM10_IRQHandler(void);      /* TIM1 Update and TIM10                       */
__attribute__((weak, alias("Default_Handler"))) void TIM1_TRG_COM_TIM11_IRQHandler(void); /* TIM1 Trigger and Commutation and TIM11      */
__attribute__((weak, alias("Default_Handler"))) void TIM1_CC_IRQHandler(void);            /* TIM1 Capture Compare                        */
__attribute__((weak, alias("Default_Handler"))) void TIM2_IRQHandler(void);               /* TIM2                                        */
__attribute__((weak, alias("Default_Handler"))) void TIM3_IRQHandler(void);               /* TIM3                                        */
__attribute__((weak, alias("Default_Handler"))) void TIM4_IRQHandler(void);               /* TIM4                                        */
__attribute__((weak, alias("Default_Handler"))) void I2C1_EV_IRQHandler(void);            /* I2C1 Event                                  */
__attribute__((weak, alias("Default_Handler"))) void I2C1_ER_IRQHandler(void);            /* I2C1 Error                                  */
__attribute__((weak, alias("Default_Handler"))) void I2C2_EV_IRQHandler(void);            /* I2C2 Event                                  */
__attribute__((weak, alias("Default_Handler"))) void I2C2_ER_IRQHandler(void);            /* I2C2 Error                                  */
__attribute__((weak, alias("Default_Handler"))) void SPI1_IRQHandler(void);               /* SPI1                                        */
__attribute__((weak, alias("Default_Handler"))) void SPI2_IRQHandler(void);               /* SPI2                                        */
__attribute__((weak, alias("Default_Handler"))) void USART1_IRQHandler(void);             /* USART1                                      */
__attribute__((weak, alias("Default_Handler"))) void USART2_IRQHandler(void);             /* USART2                                      */
__attribute__((weak, alias("Default_Handler"))) void USART3_IRQHandler(void);             /* USART3                                      */
__attribute__((weak, alias("Default_Handler"))) void EXTI15_10_IRQHandler(void);          /* External Line[15:10]s                       */
__attribute__((weak, alias("Default_Handler"))) void RTC_Alarm_IRQHandler(void);          /* RTC Alarm (A and B) through EXTI Line       */
__attribute__((weak, alias("Default_Handler"))) void OTG_FS_WKUP_IRQHandler(void);        /* USB OTG FS Wakeup through EXTI line         */
__attribute__((weak, alias("Default_Handler"))) void TIM8_BRK_TIM12_IRQHandler(void);     /* TIM8 Break and TIM12                        */
__attribute__((weak, alias("Default_Handler"))) void TIM8_UP_TIM13_IRQHandler(void);      /* TIM8 Update and TIM13                       */
__attribute__((weak, alias("Default_Handler"))) void TIM8_TRG_COM_TIM14_IRQHandler(void); /* TIM8 Trigger and Commutation and TIM14      */
__attribute__((weak, alias("Default_Handler"))) void TIM8_CC_IRQHandler(void);            /* TIM8 Capture Compare                        */
__attribute__((weak, alias("Default_Handler"))) void DMA1_Stream7_IRQHandler(void);       /* DMA1 Stream7                                */
__attribute__((weak, alias("Default_Handler"))) void FMC_IRQHandler(void);                /* FMC                                         */
__attribute__((weak, alias("Default_Handler"))) void SDIO_IRQHandler(void);               /* SDIO                                        */
__attribute__((weak, alias("Default_Handler"))) void TIM5_IRQHandler(void);               /* TIM5                                        */
__attribute__((weak, alias("Default_Handler"))) void SPI3_IRQHandler(void);               /* SPI3                                        */
__attribute__((weak, alias("Default_Handler"))) void UART4_IRQHandler(void);              /* UART4                                       */
__attribute__((weak, alias("Default_Handler"))) void UART5_IRQHandler(void);              /* UART5                                       */
__attribute__((weak, alias("Default_Handler"))) void TIM6_DAC_IRQHandler(void);           /* TIM6 and DAC1&2 underrun errors             */
__attribute__((weak, alias("Default_Handler"))) void TIM7_IRQHandler(void);               /* TIM7                                        */
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream0_IRQHandler(void);       /* DMA2 Stream 0                               */
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream1_IRQHandler(void);       /* DMA2 Stream 1                               */
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream2_IRQHandler(void);       /* DMA2 Stream 2                               */
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream3_IRQHandler(void);       /* DMA2 Stream 3                               */
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream4_IRQHandler(void);       /* DMA2 Stream 4                               */
__attribute__((weak, alias("Default_Handler"))) void CAN2_TX_IRQHandler(void);            /* CAN2 TX                                     */
__attribute__((weak, alias("Default_Handler"))) void CAN2_RX0_IRQHandler(void);           /* CAN2 RX0                                    */
__attribute__((weak, alias("Default_Handler"))) void CAN2_RX1_IRQHandler(void);           /* CAN2 RX1                                    */
__attribute__((weak, alias("Default_Handler"))) void CAN2_SCE_IRQHandler(void);           /* CAN2 SCE                                    */
__attribute__((weak, alias("Default_Handler"))) void OTG_FS_IRQHandler(void);             /* USB OTG FS                                  */
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream5_IRQHandler(void);       /* DMA2 Stream 5                               */
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream6_IRQHandler(void);       /* DMA2 Stream 6                               */
__attribute__((weak, alias("Default_Handler"))) void DMA2_Stream7_IRQHandler(void);       /* DMA2 Stream 7                               */
__attribute__((weak, alias("Default_Handler"))) void USART6_IRQHandler(void);             /* USART6                                      */
__attribute__((weak, alias("Default_Handler"))) void I2C3_EV_IRQHandler(void);            /* I2C3 event                                  */
__attribute__((weak, alias("Default_Handler"))) void I2C3_ER_IRQHandler(void);            /* I2C3 error                                  */
__attribute__((weak, alias("Default_Handler"))) void OTG_HS_EP1_OUT_IRQHandler(void);     /* USB OTG HS End Point 1 Out                  */
__attribute__((weak, alias("Default_Handler"))) void OTG_HS_EP1_IN_IRQHandler(void);      /* USB OTG HS End Point 1 In                   */
__attribute__((weak, alias("Default_Handler"))) void OTG_HS_WKUP_IRQHandler(void);        /* USB OTG HS Wakeup through EXTI              */
__attribute__((weak, alias("Default_Handler"))) void OTG_HS_IRQHandler(void);             /* USB OTG HS                                  */
__attribute__((weak, alias("Default_Handler"))) void DCMI_IRQHandler(void);               /* DCMI                                        */
__attribute__((weak, alias("Default_Handler"))) void FPU_IRQHandler(void);                /* FPU                                         */
__attribute__((weak, alias("Default_Handler"))) void SPI4_IRQHandler(void);               /* SPI4                                        */
__attribute__((weak, alias("Default_Handler"))) void SAI1_IRQHandler(void);               /* SAI1                                        */
__attribute__((weak, alias("Default_Handler"))) void SAI2_IRQHandler(void);               /* SAI2                                        */
__attribute__((weak, alias("Default_Handler"))) void QUADSPI_IRQHandler(void);            /* QuadSPI                                     */
__attribute__((weak, alias("Default_Handler"))) void CEC_IRQHandler(void);                /* CEC                                         */
__attribute__((weak, alias("Default_Handler"))) void SPDIF_RX_IRQHandler(void);           /* SPDIF RX                                    */
__attribute__((weak, alias("Default_Handler"))) void FMPI2C1_EV_IRQHandler(void);         /* FMPI2C 1 Event                              */
__attribute__((weak, alias("Default_Handler"))) void FMPI2C1_ER_IRQHandler(void);         /* FMPI2C 1 Error                              */

/* all interrupts are aliased to this Default Handler so that the system
state is preserved if an interrupt that doesn't have a handler is executed */
void Default_Handler(void)
{
    while (1) {}
}

/* vector table, 16 cortex vectors + 96 ST vectors */
__attribute__((section(".isr_vector"), used)) void (* const vector_table[113])(void) = {
    /* initial stack pointer */
    (void (*)(void))&_estack, 

    /* cortex-m4 processor exceptions */
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,

    /* stm32f446xx interrupts */
    WWDG_IRQHandler,
    PVD_IRQHandler,
    TAMP_STAMP_IRQHandler,
    RTC_WKUP_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler,
    EXTI3_IRQHandler,
    EXTI4_IRQHandler,
    DMA1_Stream0_IRQHandler,
    DMA1_Stream1_IRQHandler,
    DMA1_Stream2_IRQHandler,
    DMA1_Stream3_IRQHandler,
    DMA1_Stream4_IRQHandler,
    DMA1_Stream5_IRQHandler,
    DMA1_Stream6_IRQHandler,
    ADC_IRQHandler,
    CAN1_TX_IRQHandler,
    CAN1_RX0_IRQHandler,
    CAN1_RX1_IRQHandler,
    CAN1_SCE_IRQHandler,
    EXTI9_5_IRQHandler,
    TIM1_BRK_TIM9_IRQHandler,
    TIM1_UP_TIM10_IRQHandler,
    TIM1_TRG_COM_TIM11_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM4_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    I2C2_EV_IRQHandler,
    I2C2_ER_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_IRQHandler,
    EXTI15_10_IRQHandler,
    RTC_Alarm_IRQHandler,
    OTG_FS_WKUP_IRQHandler,
    TIM8_BRK_TIM12_IRQHandler,
    TIM8_UP_TIM13_IRQHandler,
    TIM8_TRG_COM_TIM14_IRQHandler,
    TIM8_CC_IRQHandler,
    DMA1_Stream7_IRQHandler,
    FMC_IRQHandler,
    SDIO_IRQHandler,
    TIM5_IRQHandler,
    SPI3_IRQHandler,
    UART4_IRQHandler,
    UART5_IRQHandler,
    TIM6_DAC_IRQHandler,
    TIM7_IRQHandler,
    DMA2_Stream0_IRQHandler,
    DMA2_Stream1_IRQHandler,
    DMA2_Stream2_IRQHandler,
    DMA2_Stream3_IRQHandler,
    DMA2_Stream4_IRQHandler,
    0,
    0,
    CAN2_TX_IRQHandler,
    CAN2_RX0_IRQHandler,
    CAN2_RX1_IRQHandler,
    CAN2_SCE_IRQHandler,
    OTG_FS_IRQHandler,
    DMA2_Stream5_IRQHandler,
    DMA2_Stream6_IRQHandler,
    DMA2_Stream7_IRQHandler,
    USART6_IRQHandler,
    I2C3_EV_IRQHandler,
    I2C3_ER_IRQHandler,
    OTG_HS_EP1_OUT_IRQHandler,
    OTG_HS_EP1_IN_IRQHandler,
    OTG_HS_WKUP_IRQHandler,
    OTG_HS_IRQHandler,
    DCMI_IRQHandler,
    0,
    0,
    FPU_IRQHandler,
    0,
    0,
    SPI4_IRQHandler,
    0,
    0,
    SAI1_IRQHandler,
    0,
    0,
    0,
    SAI2_IRQHandler,
    QUADSPI_IRQHandler,
    CEC_IRQHandler,
    SPDIF_RX_IRQHandler,
    FMPI2C1_EV_IRQHandler,
    FMPI2C1_ER_IRQHandler
};