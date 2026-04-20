#include "exti.h"

/* exti line enable with trigger selection */
void EXTI_Line_Enable(EXTI_Line line, EXTI_Trigger trigger)
{
    /* unmask selected exti line */
    EXTI->IMR |= line;

    /* set trigger */
    switch (trigger)
    {
    case EXTI_RISING_EDGE_TRIGGER:
        EXTI->RTSR |= line;
        break;
    
    case EXTI_FALLING_EDGE_TRIGGER:
        EXTI->FTSR |= line;
        break;

    case EXTI_RISING_FALLING_EDGE_TRIGGER:
        EXTI->RTSR |= line;
        EXTI->FTSR |= line;
        break;
    }
}