#include "mk_mem.h"

// TODO: the stack initialization for the software-saved context
// in both functions pushes 9 words, which leads the stack pointer to no longer
// be 8-byte aligned. Technically, this isn't an issue for the CPU,
// but it doesn't follow the ARM AAPCS.

/* track the last memory address that was allocated */
uint32_t *allocated;

void mk_mem_init(void)
{
    /* load initial stack pointer from vector table */
    uint32_t *stack = (uint32_t *)*((uint32_t *)MK_PORT_INITIAL_SP);

    /* load the current stack pointer */
    uint32_t *msp = NULL;
    __asm__ volatile ("MOV %0, sp \n" : "=r" (msp));

    /* align kernel stack size to 8 bytes */
    size_t kernelStackSize = (MK_CONFIG_KERNEL_STACK_SIZE + 7U) & ~7U;

    /* check if the current kernel stack is larger than the configured stack size */
    if (((uintptr_t)stack - (uintptr_t)msp) > kernelStackSize)
    {
        /* if kernel stack size already exceeds configured size, placed
        the cpu in debug state for further investigation */
        __asm__ volatile ("BKPT #0 \n");
    }

    /* otherwise, allocate the kernel stack */
    stack -= (kernelStackSize / sizeof(uint32_t));

    /* next, allocate the idle task stack */
    /* first, push hardware-saved cpu context */
    *(--stack) = 0x01000000;                // xPSR, with thumb state bit set
    *(--stack) = (uint32_t)mk_idleTask;     // PC
    *(--stack) = 0;                         // LR
    *(--stack) = 0;                         // R12
    *(--stack) = 0;                         // R3
    *(--stack) = 0;                         // R2
    *(--stack) = 0;                         // R1
    *(--stack) = 0;                         // R0

    /* then push software-saved cpu context (R4-R11, R14) */
    /* R14 is saved as EXC_RETURN for the PendSV handler */
    *(--stack) = 0xFFFFFFFD;                // LR (R14): EXC_RETURN (Thread mode, PSP)
    *(--stack) = 0;                         // R11
    *(--stack) = 0;                         // R10
    *(--stack) = 0;                         // R9
    *(--stack) = 0;                         // R8
    *(--stack) = 0;                         // R7
    *(--stack) = 0;                         // R6
    *(--stack) = 0;                         // R5
    *(--stack) = 0;                         // R4

    /* initialize the idle task task control block */
    _mk_taskPool[MK_CONFIG_MAX_TASKS].stackPtr      = (void *)stack;
    _mk_taskPool[MK_CONFIG_MAX_TASKS].taskHandle    = (mk_taskHandle_t)MK_CONFIG_MAX_TASKS;
    _mk_taskPool[MK_CONFIG_MAX_TASKS].next          = (mk_taskHandle_t)-1;
    _mk_taskPool[MK_CONFIG_MAX_TASKS].prev          = (mk_taskHandle_t)-1;

    /* allocate the rest of the idle task stack, currently hardcoded to 256 bytes (64 words) */
    for (int i = 0; i < 64; i++)
    {
        *(--stack) = 0;
    }

    /* update allocated address, future stacks go below this address */
    allocated = stack;
}

int mk_mem_initTaskStackFrame(mk_task_t *task, size_t size, void *entry, void *arg)
{
    /* get pointer to last byte allocated */
    uint32_t *stack = allocated;

    /* align task stack size to 8 bytes */
    size = (size + 7U) & ~7U;

    /* allocate task stack */
    /* hardware-saved cpu context */
    *(--stack) = 0x01000000;                // xPSR
    *(--stack) = (uint32_t)entry;           // PC (task entry)
    *(--stack) = 0;                         // LR
    *(--stack) = 0;                         // R12
    *(--stack) = 0;                         // R3
    *(--stack) = 0;                         // R2
    *(--stack) = 0;                         // R1
    *(--stack) = (uint32_t)arg;             // R0 (argument passed to task)

    /* software-saved cpu context (R4-R11, R14) */
    /* R14 is saved as EXC_RETURN for the PendSV handler */
    *(--stack) = 0xFFFFFFFD;                // LR (R14): EXC_RETURN (Thread mode, PSP)
    *(--stack) = 0;                         // R11
    *(--stack) = 0;                         // R10
    *(--stack) = 0;                         // R9
    *(--stack) = 0;                         // R8
    *(--stack) = 0;                         // R7
    *(--stack) = 0;                         // R6
    *(--stack) = 0;                         // R5
    *(--stack) = 0;                         // R4

    /* update task stack pointer */
    task->stackPtr = stack;

    /* allocate the rest of the task's stack, taking into account
    the 68 bytes already allocated for cpu context (17 words) */
    for (unsigned int i = 0; i < ((size - 68) / sizeof(uint32_t)); i++)
    {
        *(--stack) = 0;
    }

    allocated = stack;

    return 0;
}
