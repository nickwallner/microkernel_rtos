#ifndef ARM_CM4F_PORT
#define ARM_CM4F_PORT

#include <stdint.h>
#include "mk_config.h"
#include "mk_scheduler.h"

#define BIT(x) ( 1UL << x )

/* the address where the initial stack pointer is stored */
#define MK_PORT_INITIAL_SP 0x00000000

/* systick registers and control bits */
#define MK_PORT_SYSTICK_CTRL_REG        ( *( ( volatile uint32_t * ) 0xe000e010 ) )
#define MK_PORT_SYSTICK_LOAD_REG        ( *( ( volatile uint32_t * ) 0xe000e014 ) )
#define MK_PORT_SYSTICK_VAL_REG         ( *( ( volatile uint32_t * ) 0xe000e018 ) )
#define MK_PORT_SYSTICK_ENABLE_BIT      BIT(0)
#define MK_PORT_SYSTICK_EXCEPTION_BIT   BIT(1)
#define MK_PORT_SYSTICK_CLOCK_BIT       BIT(2)

/* interrupt control and state register and control bits */
#define MK_PORT_INTERRUPT_CTRL_REG          ( *( ( volatile uint32_t * ) 0xe000ed04 ) )
#define MK_PORT_PENDSV_INTERRUPT_SET_BIT    BIT(28)
#define MK_PORT_PENDSV_INTERRUPT_CLEAR_BIT  BIT(27)

/* system handler priority register 3 and control bits */
#define MK_PORT_SHPR3_REG   ( *( ( volatile uint32_t * ) 0xe000ed20 ) )
#define MK_PORT_PENDSV_PRI  ( 255UL << 16UL ) // pendsv interrupt gets lowest priority
#define MK_PORT_SYSTICK_PRI ( 255UL << 24UL ) // systick interrupt also gets lowest priority

/* macros for setting and clearing a pending SV interrupt */
#define MK_PORT_SET_PENDSV_INTERRUPT()      do { \
                                                MK_PORT_INTERRUPT_CTRL_REG |= MK_PORT_PENDSV_INTERRUPT_SET_BIT; \
                                            } while(0)
#define MK_PORT_CLEAR_PENDSV_INTERRUPT()    do { \
                                                MK_PORT_INTERRUPT_CTRL_REG |= MK_PORT_PENDSV_INTERRUPT_CLEAR_BIT; \
                                            } while(0)

/* macros to disable and enable interrupts */
#define MK_PORT_DISABLE_INTERRUPTS()    do { \
                                            __asm__ volatile ("cpsid i \n"); \
                                        } while (0)

#define MK_PORT_ENABLE_INTERRUPTS()     do { \
                                            __asm__ volatile ("cpsie i \n"); \
                                        } while (0)

void mk_port_start(void);
void mk_port_startFirstTask(void) __attribute__((naked));
void mk_port_reschedule(void);

void SysTick_Handler(void);
void PendSV_Handler(void) __attribute__((naked));

#endif // ARM_CM4F_PORT
