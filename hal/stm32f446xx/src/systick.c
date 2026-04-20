#include "systick.h"

volatile uint64_t ticks = 0; // systick tick counter

inline void SYSTICK_Inc_Ticks(void)
{
    ticks++;
}

void SYSTICK_Init(uint32_t freq, SYSTICK_Time_Interval interval)
{
    uint32_t tickrate = freq / interval;

    if ((tickrate - 1) > 0xffffff) return; // the systick timer is 24-bit

    SYSTICK->SYST_RVR = tickrate - 1; // set the reload value
    SYSTICK->SYST_CVR = 0; // clear the current value

    SYSTICK->SYST_CSR = BIT(0) | BIT(1) | BIT(2); // enable the systick timer
}

void SYSTICK_Delay(uint32_t delay_period)
{
    uint64_t until = ticks + delay_period;
    while (ticks < until) {}
}
