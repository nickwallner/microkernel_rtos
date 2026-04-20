# OS BUGS

BUG: `mk_task_initTasks()` was overwriting the TCB for the idle task after `mk_mem_init()` had
already set the stack pointer for the idle task
FIX: removed all idle task initialization from `mk_task_initTasks()` and moved it to `mk_mem_init()`

BUG: `_mk_currentTaskID` was initialized to zero instead of 1
FIX: change `_mk_currentTaskID` to be initialized to zero

BUG: `SysTick_Handler` in `port.c` was named incorrectly, leading to the `Default_Handler` to be
called in place of the `SysTick_Handler` for all Systick interrupts.
FIX: renamed `SysTick_Handler` appropriately

BUG: Kernel initialization functions need to be called before trying to make a new task. I attempted
to combine `mk_initKernel` into the `mk_startKernel` function, but you call `mk_createTask` before
calling `mk_startKernel`. `mk_createTask` does some memory initialization, so this leads to a hard fault
by dereferencing a null pointer.
FIX: keep kernel initialization and starting separate for now
