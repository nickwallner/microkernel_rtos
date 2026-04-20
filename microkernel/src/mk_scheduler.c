#include "mk_scheduler.h"

/* scheduler variables */
mk_queue_t          mk_readyTasks[MK_CONFIG_PRIORITY_LEVELS];
mk_taskHandle_t     mk_waitingTasksHead;
mk_taskHandle_t     mk_stoppedTasksHead;
mk_taskHandle_t     mk_taskQueueStorage[MK_CONFIG_PRIORITY_LEVELS * MK_CONFIG_MAX_TASKS];
uint32_t            mk_taskPriorityBitmap;

int mk_sched_addReadyTask(mk_task_t *task)
{
    /* get pointer to queue for task's priority */
    mk_queue_t *q = &(mk_readyTasks[task->priority]);

    /* push task index to queue */
    if (!q_push(q, &task->taskHandle))
    {
        return -1;
    }

    task->state = READY;

    /* set bit in priority bitmap */
    mk_taskPriorityBitmap |= (1UL << (31 - task->priority));

    return 0;
}

int mk_sched_removeReadyTask(mk_task_t *task)
{
    mk_queue_t *q = &mk_readyTasks[task->priority];

    int size = q_getCount(q);
    int found = 0;
    mk_taskHandle_t handle = 0;

    /* rotate queue by popping each task, checking if task matches
    passed task, and then pushing task back to queue unless it matches
    the passed task */
    for (int i = 0; i < size; i++)
    {
        /* pop task */
        if (!q_pop(q, &handle))
        {
            return -1;
        }

        /* only push task back into queue if it doesn't match
        the passed task */
        if (handle == task->taskHandle)
        {
            found = 1;
        }
        else
        {
            if (!q_push(q, &handle))
            {
                return -1;
            }
        }
    }

    /* if the queue is empty after removing the task, reset
    that queue's bit in the priority bitmap */
    if (q_isEmpty(q))
    {
        mk_taskPriorityBitmap &= ~(1UL << (31 - task->priority));
    }
    
    return found ? 0 : -1;
}

int mk_sched_addWaitingTask(mk_task_t *task)
{
    mk_taskHandle_t current_idx = mk_waitingTasksHead;
    mk_taskHandle_t prev_idx = -1;

    task->state = WAITING;

    /* if list is empty */
    if (current_idx == -1) {
        mk_waitingTasksHead = task->taskHandle;
        task->next = -1;
        task->prev = -1;
        return 0;
    }

    /* if list is not empty, traverse list to find correct insertion point 
    to keep the list sorted by task wake time (ascending) */
    while (current_idx != -1)
    {
        mk_task_t *curr = &_mk_taskPool[current_idx];
        
        if (task->wakeTime < curr->wakeTime)
        {
            /* insert new task in front of current task */
            task->next = current_idx;
            task->prev = curr->prev;
            curr->prev = task->taskHandle;
            
            /* check if there are other tasks in front of new task */
            if (task->prev != -1)
            {
                /* update task in front of new task */
                _mk_taskPool[task->prev].next = task->taskHandle;
            }
            else
            {
                /* otherwise, new task is at the front of the list */
                mk_waitingTasksHead = task->taskHandle;
            }

            return 0;
        }
        
        prev_idx = current_idx;
        current_idx = curr->next;
    }

    /* insert new task at end of list */
    if (prev_idx != -1)
    {
        _mk_taskPool[prev_idx].next = task->taskHandle;
        task->prev = prev_idx;
        task->next = -1;
    }

    return 0;
}

/**
 * @brief Remove the task at the front of the waiting list
 * 
 * @return 0 if successful, -1 on error
 */
int mk_sched_removeWaitingTask(void)
{
    if (mk_waitingTasksHead != -1)
    {
        mk_waitingTasksHead = _mk_taskPool[mk_waitingTasksHead].next;

        /* update prev idx if there are still other waiting tasks */
        if (mk_waitingTasksHead != -1)
        {
            _mk_taskPool[mk_waitingTasksHead].prev = -1;
        }

        return 0;
    }

    return -1;
}

int mk_sched_addStoppedTask(mk_task_t *task)
{
    /* order doesn't matter for stopped tasks, so just
    place new task at the front of the list */
    task->next = mk_stoppedTasksHead;
    mk_stoppedTasksHead = task->taskHandle;

    task->state = STOPPED;

    return 0;
}

int mk_sched_getNextTask(void)
{
    /* if there are no tasks ready to run, and current is no longer runnable, 
    then run the idle task */
    if ((mk_taskPriorityBitmap == 0) && (_mk_currentTask->state != READY))
    {
        _mk_currentTask = &_mk_taskPool[MK_CONFIG_MAX_TASKS];
        _mk_currentTask->state = READY;

        return 0;
    }

    mk_taskPriority_t highestPriority = (mk_taskPriority_t)__builtin_clz(mk_taskPriorityBitmap);

    /* only switch task if: 
       current task is blocked (WAITING/STOPPED)
       OR a higher priority task is ready
       OR a task of same priority is ready and current task's time slice expired */
    if ((_mk_currentTask->state != READY) || 
        (highestPriority < _mk_currentTask->priority) || 
        ((highestPriority == _mk_currentTask->priority) && (_mk_currentTask->timeLeft == 0)))
    {
        mk_taskHandle_t nextTask;

        if (!q_peek(&mk_readyTasks[highestPriority], &nextTask))
        {
            return -1;
        }

        /* only return current task to ready queue IF:
            its state is still READY
            AND its not the idle task */
        if ((_mk_currentTask->state == READY) &&
            (_mk_currentTask->taskHandle != MK_CONFIG_MAX_TASKS))
        {
            mk_sched_addReadyTask(_mk_currentTask);
        }

        /* update current task global with next task to run */
        _mk_currentTask = &_mk_taskPool[nextTask];
        _mk_currentTask->state = READY;
        _mk_currentTask->timeLeft = _mk_currentTask->timeSlice;
    }

    return 0;
}

int mk_sched_incrementSystemTick(void)
{
    int reschedule = 0;

    _mk_kernelTickCount++;
 
    /* wake any tasks whose wakeTime is less than or equal to the current tick count */
    mk_taskHandle_t current_idx = mk_waitingTasksHead;
    while (current_idx != -1 && _mk_taskPool[current_idx].wakeTime <= _mk_kernelTickCount)
    {
        mk_task_t *wokenTask = &_mk_taskPool[current_idx];

        /* check if woken task has higher priority than current task to
        determine if a reschedule is necessary */
        if (wokenTask->priority < _mk_currentTask->priority)
        {
            reschedule = 1;
        }

        mk_sched_addReadyTask(wokenTask);
        mk_sched_removeWaitingTask();

        current_idx = mk_waitingTasksHead;
    }

    /* update current task time slice */
    if (_mk_currentTask != NULL)
    {
        /* check for underflow and decrement current task time slice */
        if (_mk_currentTask->timeLeft > MK_SCHED_MS_PER_TICK)
        {
            _mk_currentTask->timeLeft -= MK_SCHED_MS_PER_TICK;
        }
        else
        {
            _mk_currentTask->timeLeft = 0;
            reschedule = 1;
        }
    }

    /* reschedule if time slice expired or a higher priority task is ready */
    if (reschedule)
    {
        return 1;
    }

    return 0;
}

void mk_sched_waitTask(mk_task_t *task, uint32_t time)
{
    task->wakeTime = _mk_kernelTickCount + time;

    if (task->state == READY)
    {
        mk_sched_removeReadyTask(task);
    }
    
    task->state = WAITING;
    
    mk_sched_addWaitingTask(task);
    mk_port_reschedule();
}

void mk_sched_yieldTask(mk_task_t *task)
{
    task->timeLeft = 0; // force a reschedule on next check
    mk_port_reschedule();
}

void mk_sched_stopTask(mk_task_t *task)
{
    if (task->state == READY)
    {
        mk_sched_removeReadyTask(task);
    }

    task->state = STOPPED;

    mk_sched_addStoppedTask(task);
    mk_port_reschedule();
}

int mk_sched_init(void)
{
    /* initialize each task queue */
    for (int i = 0; i < MK_CONFIG_PRIORITY_LEVELS; i++)
    {
        /* all queues are stored in the same mk_taskQueueStorage array because
        they are all statically allocated */
        q_init_static(&mk_readyTasks[i], sizeof(mk_taskHandle_t), MK_CONFIG_MAX_TASKS, 
                        FIFO, false, mk_taskQueueStorage + (MK_CONFIG_MAX_TASKS * i), 
                        (MK_CONFIG_MAX_TASKS * sizeof(mk_taskHandle_t)));
    }

    mk_waitingTasksHead = -1;
    mk_stoppedTasksHead = -1;
    mk_taskPriorityBitmap = 0;

    /* initialize the idle task, it is at the last index of _mk_taskPool */
    mk_task_t *idleTask = &_mk_taskPool[MK_CONFIG_MAX_TASKS];

    idleTask->priority  = MK_CONFIG_PRIORITY_LEVELS - 1; // lowest priority level
    idleTask->state     = READY;
    idleTask->timeSlice = MK_CONFIG_TASK_TIME_SLICE_MS;
    idleTask->timeLeft  = MK_CONFIG_TASK_TIME_SLICE_MS;
    idleTask->taskID    = 0; // id 0 reserved for idle task

    return 0;
}

int mk_sched_start(void)
{
    /* initially set the current task to the idle task */
    _mk_currentTask = &_mk_taskPool[MK_CONFIG_MAX_TASKS];

    /* update the current task with the next task to run */
    if (mk_sched_getNextTask() != 0)
    {
        return -1;
    }

    /* start hardware timer and jump to first task entry */
    mk_port_start();

    return 0; // execution should never reach here
}
