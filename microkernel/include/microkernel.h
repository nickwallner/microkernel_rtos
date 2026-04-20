#ifndef MICROKERNEL_H_
#define MICROKERNEL_H_

#include "mk_common.h"
#include "mk_mem.h"
#include "mk_queue.h"
#include "mk_scheduler.h"
#include "mk_task.h"

// TODO: make enum for errors like errno?

/**
 * @brief Initialize the kernel. This function MUST be called
 * prior to calling any other kernel functions.
 * 
 */
void mk_initKernel(void);

/**
 * @brief Start the kernel. This function MUST be called AFTER initializing
 * the kernel and BEFORE calling any task manipulation functions (e.g. task
 * wait or task stop).
 * 
 * @return 0 if successful, -1 on error
 */
int mk_startKernel(void);

/**
 * @brief Create a new task.
 * 
 * @param entry pointer to the task's entry address
 * @param arg argument to be passed to the task upon entry, or NULL for no argument
 * @param stackSize size of the task's stack in bytes, minimum 64 bytes
 * @param priority priority of the task, must be <= MK_CONFIG_PRIORITY_LEVELS
 * @return ID of the newly created task
 */
mk_taskID_t mk_createTask(void *entry, void *arg, size_t stackSize, mk_taskPriority_t priority);

/**
 * @brief Get the ID of the currently running task.
 * 
 * @return The ID of the current task
 */
mk_taskID_t mk_getCurrentTaskID(void);

/**
 * @brief Make a task wait for a specific period of time.
 * 
 * @param task ID of the task to wait
 * @param time Duration that the task will wait (ms)
 * @return 0 if successful, -1 on error
 */
int mk_waitTask(mk_taskID_t task, uint32_t time);

/**
 * @brief Allow a task to yield its remaining CPU time
 * 
 * @param task ID of the task yielding
 * @return 0 if successful, -1 on error
 */
int mk_yieldTask(mk_taskID_t task);

/**
 * @brief Stop a task.
 * 
 * @param task ID of the task to stop
 * @return 0 if successful, -1 on error
 */
int mk_stopTask(mk_taskID_t task);

#endif // MICROKERNEL_H_
