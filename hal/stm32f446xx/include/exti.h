#ifndef EXTI_H_
#define EXTI_H_

#include "common.h"

/* exti peripheral base address */
#define EXTI_PERIPH_BASE_ADDR   0x40013C00
#define SYSCFG_PERIPH_BASE_ADDR 0x40013800

/* exti peripheral */
#define EXTI        ((EXTI_Peripheral *)        EXTI_PERIPH_BASE_ADDR)
#define SYSCFG_EXTI ((SYSCFG_EXTI_Peripheral *) SYSCFG_PERIPH_BASE_ADDR)

/* exti peripheral registers */
typedef struct
{
    volatile uint32_t IMR;   // EXTI interrupt mask register
    volatile uint32_t EMR;   // EXTI event mask register
    volatile uint32_t RTSR;  // EXTI rising edge trigger selection register
    volatile uint32_t FTSR;  // EXTI falling edge trigger selection register
    volatile uint32_t SWIER; // EXTI software interrupt event register
    volatile uint32_t PR;    // EXTI pending register
} EXTI_Peripheral;

/* syscfg registers that are used
for configuring exti */
typedef struct
{
             uint32_t UNUSED0[2];
    volatile uint32_t EXTICR1; // SYSCFG external interrupt configuration register 1
    volatile uint32_t EXTICR2; // SYSCFG external interrupt configuration register 2
    volatile uint32_t EXTICR3; // SYSCFG external interrupt configuration register 3
    volatile uint32_t EXTICR4; // SYSCFG external interrupt configuration register 4
} SYSCFG_EXTI_Peripheral;

/* enums for each of the 23 exti interrupt lines */
typedef enum
{
    EXTI_LINE_0  = BIT(0),
    EXTI_LINE_1  = BIT(1),
    EXTI_LINE_2  = BIT(2),
    EXTI_LINE_3  = BIT(3),
    EXTI_LINE_4  = BIT(4),
    EXTI_LINE_5  = BIT(5),
    EXTI_LINE_6  = BIT(6),
    EXTI_LINE_7  = BIT(7),
    EXTI_LINE_8  = BIT(8),
    EXTI_LINE_9  = BIT(9),
    EXTI_LINE_10 = BIT(10),
    EXTI_LINE_11 = BIT(11),
    EXTI_LINE_12 = BIT(12),
    EXTI_LINE_13 = BIT(13),
    EXTI_LINE_14 = BIT(14),
    EXTI_LINE_15 = BIT(15),
    EXTI_LINE_16 = BIT(16),
    EXTI_LINE_17 = BIT(17),
    EXTI_LINE_18 = BIT(18),
    EXTI_LINE_19 = BIT(19),
    EXTI_LINE_20 = BIT(20),
    EXTI_LINE_21 = BIT(21),
    EXTI_LINE_22 = BIT(22)
} EXTI_Line;

/* exti interrupt trigger types */
typedef enum
{
    EXTI_RISING_EDGE_TRIGGER,
    EXTI_FALLING_EDGE_TRIGGER,
    EXTI_RISING_FALLING_EDGE_TRIGGER,
} EXTI_Trigger;

/**
 * @brief Enable an EXTI line on a specific trigger
 * 
 * @param line EXTI line to enable
 * @param trigger EXTI line trigger
 */
void EXTI_Line_Enable(EXTI_Line line, EXTI_Trigger trigger);

#endif // EXTI_H_