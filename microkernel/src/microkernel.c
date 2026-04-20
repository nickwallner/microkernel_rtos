#include "microkernel.h"

// TODO: task IDs are incremented but never decremented, but does it really matter? (i dont think so)

uint8_t kernel_initialized  = 0; // track if the kernel has been initialized
uint8_t kernel_started      = 0; // track if the kernel has been started

void mk_initKernel(void)
{
    /* these initialization functions MUST be called in
    this specific order! */
    mk_mem_init();
    mk_task_init();
    mk_sched_init();

    kernel_initialized = 1;
}

int mk_startKernel(void)
{
    if (!kernel_initialized) return -1;

    kernel_started = 1;

    mk_sched_start();

    return 0;
}

mk_taskID_t mk_createTask(void *entry, void *arg, size_t stackSize, mk_taskPriority_t priority)
{
    if (!kernel_initialized) return (mk_taskID_t)-1;

    /* validate priority level */
    if (priority >= MK_CONFIG_PRIORITY_LEVELS)
    {
        return (mk_taskID_t)-1;
    }

    /* validate stack size */
    if (stackSize < 64)
    {
        return (mk_taskID_t)-1;
    }

    /* iterate through the task pool to find an unused task */
    for (int i = 0; i < MK_CONFIG_MAX_TASKS; i++)
    {
        if (_mk_taskPool[i].stackPtr == NULL)
        {
            mk_task_t *task = &_mk_taskPool[i];

            /* initialize task control block fields */
            task->priority  = priority;
            task->timeSlice = MK_CONFIG_TASK_TIME_SLICE_MS;
            task->timeLeft  = MK_CONFIG_TASK_TIME_SLICE_MS;
            task->wakeTime  = 0;
            task->taskID    = _mk_currentTaskID++;

            /* initialize the new task's stack frame */
            if (mk_mem_initTaskStackFrame(task, stackSize, entry, arg) != 0)
            {
                return (mk_taskID_t)-1;
            }

            /* register the task with the scheduler to make it eligible for execution */
            if (mk_sched_addReadyTask(task) != 0)
            {
                return (mk_taskID_t)-1;
            }

            return task->taskID;
        }
    }

    /* return error if no task slots are available */
    return (mk_taskID_t)-1;
}

mk_taskID_t mk_getCurrentTaskID(void)
{
    if (!kernel_started) return (mk_taskID_t)-1;

    return _mk_currentTask->taskID;
}

int mk_waitTask(mk_taskID_t task, uint32_t time)
{
    if (!kernel_started) return -1;

    mk_sched_waitTask(mk_task_getTaskByID(task), time);

    return 0;
}

int mk_yieldTask(mk_taskID_t task)
{
    if (!kernel_started) return -1;

    mk_sched_yieldTask(mk_task_getTaskByID(task));

    return 0;
}

int mk_stopTask(mk_taskID_t task)
{
    if (!kernel_started) return -1;
    
    mk_sched_stopTask(mk_task_getTaskByID(task));

    return 0;
}
