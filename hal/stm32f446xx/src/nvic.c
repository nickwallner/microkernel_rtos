#include "nvic.h"

void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    if ((int32_t)(IRQn) >= 0)
    {
        NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    }
}