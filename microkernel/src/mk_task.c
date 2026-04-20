#include "mk_task.h"

void mk_task_init(void)
{
    /* initialize each task in the task pool */
    for (int i = 0; i < MK_CONFIG_MAX_TASKS; i++)
    {
        _mk_taskPool[i].stackPtr = NULL;
        _mk_taskPool[i].taskHandle = (mk_taskHandle_t)i;
        _mk_taskPool[i].next = -1;
        _mk_taskPool[i].prev = -1;
    }
}

mk_task_t *mk_task_getTaskByID(mk_taskID_t taskID)
{
    /* iterate through the entire task pool, including the idle task at the last index */
    for (int i = 0; i <= MK_CONFIG_MAX_TASKS; i++)
    {
        if (_mk_taskPool[i].taskID == taskID)
        {
            /* verify the task is active by checking the stack pointer
               Note: the idle task (index MK_CONFIG_MAX_TASKS) is always considered active */
            if ((i == MK_CONFIG_MAX_TASKS) || (_mk_taskPool[i].stackPtr != NULL))
            {
                return &_mk_taskPool[i];
            }
        }
    }

    return NULL;
}
