#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "common.h"

/* base address for the systick timer */
#define SYSTICK_BASE_ADDR 0xE000E010

/* systick timer peripheral */
#define SYSTICK ((SYSTICK_Peripheral *) SYSTICK_BASE_ADDR)

/* systick peripheral struct */
typedef struct
{
    volatile uint32_t SYST_CSR;   // SYSTICK control and status register
    volatile uint32_t SYST_RVR;   // SYSTICK reset value register
    volatile uint32_t SYST_CVR;   // SYSTICK current value register
    volatile uint32_t SYST_CALIB; // SYSTICK calibration register
} SYSTICK_Peripheral;

/* systick timer intervals */
/* this value determines the frequency at which the systick timer
will generate systick exceptions */
typedef enum
{
    SYSTICK_US  = 1000000U, // systick interrupt generated each microsecond
    SYSTICK_MS  = 1000U,    // systick interrupt generated each millisecond
    SYSTICK_SEC = 1U,       // systick interrupt generated each second
} SYSTICK_Time_Interval;

/**
 * @brief Increments the systick tick counter by one
 */
void SYSTICK_Inc_Ticks(void);

/**
 * @brief Initializes the systick timer
 * 
 * @param freq System operating frequency
 * @param interval Selected systick time interval
 */
void SYSTICK_Init(uint32_t freq, SYSTICK_Time_Interval interval);

/**
 * @brief Delay all execution for delay_period
 * 
 * @param delay_period Delay period
 * 
 * @details The length of the delay period depends on how systick
 * was initialized. For instance, if systick was initialized using SYSTICK_MS,
 * then `delay_period` is a value in milliseconds
 */
void SYSTICK_Delay(uint32_t delay_period);

#endif // SYSTICK_H_