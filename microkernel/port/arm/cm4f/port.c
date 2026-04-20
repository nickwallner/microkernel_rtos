#include "port.h"

static inline void systick_init(void)
{
    uint32_t loadval = MK_CONFIG_SYS_FREQ_HZ / MK_CONFIG_SYS_TICK_RATE_HZ;

    if (loadval <= 0xffffff) // systick timer is 24 bit
    {
        MK_PORT_SYSTICK_LOAD_REG = loadval - 1;
        MK_PORT_SYSTICK_VAL_REG  = 0;
        MK_PORT_SYSTICK_CTRL_REG = (MK_PORT_SYSTICK_ENABLE_BIT | MK_PORT_SYSTICK_EXCEPTION_BIT | MK_PORT_SYSTICK_CLOCK_BIT);
    }
}

void mk_port_start(void)
{
    /* set pendSV and systick interrupt priorities */
    MK_PORT_SHPR3_REG = (MK_PORT_PENDSV_PRI | MK_PORT_SYSTICK_PRI);

    /* initialize systick timer */
    systick_init();

    /* start the first task, this function shouldn't ever return */
    mk_port_startFirstTask();

    /* infinite loop just in case the function above returns for some reason */
    while (1) {}
}

void mk_port_startFirstTask(void)
{
    __asm__ volatile (
        /* load the current task stack pointer into psp */
        "ldr r0, =_mk_currentTask           \n"
        "ldr r1, [r0]                       \n"
        "ldr r2, [r1]                       \n"
        "msr psp, r2                        \n"

        /* switch to thread mode to use psp as the stack pointer */
        "mov r0, #2                         \n"
        "msr control, r0                    \n"
        "isb                                \n"

        /* pop software-saved task context */
        "ldmia sp!, {r4-r11}                \n"
        "add sp, sp, #4                     \n" // skip EXC_RETURN word
        
        /* pop hardware-saved context: R0-R3, R12, LR */
        "ldmia sp!, {r0-r3, r12, lr}        \n"
        
        /* enable interrupts */
        "cpsie i                            \n"

        /* pop pc to jump to first task entry */
        "pop {pc}                           \n"
    );
}

void mk_port_reschedule(void)
{
    MK_PORT_SET_PENDSV_INTERRUPT();
}

void SysTick_Handler(void)
{
    if (mk_sched_incrementSystemTick())
    {
        /* a context switch is required, so set the pendSV interrupt
        bit to request a pendSV interrupt */
        MK_PORT_SET_PENDSV_INTERRUPT();
    }
}

void PendSV_Handler(void)
{
    /* perform a context switch */
    __asm__ volatile
    (
        /* load the program stack pointer into r0 */
        "mrs r0, psp                        \n"

        /* load the address of the TCB for the 
        task currently running into r2 */
        "ldr r3, =_mk_currentTask           \n"
        "ldr r2, [r3]                       \n"

        /* now save all other general purpose registers 
        not saved automatically and save the EXEC_RETURN 
        value in the link register (r14) */
        "stmdb r0!, {r4-r11, r14}           \n"

        /* update current task control block stack pointer */
        "str r0, [r2]                       \n"

        /* save registers before calling scheduler so
        they don't get clobbered, only r0 and r3 need 
        to be saved, but we save 4 registers total to
        keep the stack pointer aligned to 8 bytes */
        "push {r0, r3, r12, lr}             \n"

        /* call scheduler to update _mk_currentTask 
        with next task to run */
        "bl mk_sched_getNextTask            \n"

        /* restore registers after scheduler call */
        "pop {r0, r3, r12, lr}              \n"

        /* load the address of new task control block into r2 */
        "ldr r2, [r3]                       \n"

        /* load stack pointer from new task into r0 */
        "ldr r0, [r2]                       \n" 

        /* load general purpose registers and 
        EXEC_RETURN value */
        "ldmia r0!, {r4-r11, r14}           \n"

        /* update program stack pointer */
        "msr psp, r0                        \n"
        "isb                                \n"

        /* return from exception handler */
        "bx r14                             \n"
    );
}
