#ifndef MK_SCHEDULER_H_
#define MK_SCHEDULER_H_

#include "mk_common.h"
#include "port.h"

/* TODO: when should a task's time slice be reset when rescheduling? */

/* calculate how many milliseconds elapse between each system tick,
this is used for tracking task time slices */
#define MK_SCHED_MS_PER_TICK (1000 / MK_CONFIG_SYS_TICK_RATE_HZ)

/**
 * @brief Add a task into the appropriate ready queue, update the task's status, 
 * and update the task priority bitmap
 * 
 * @param task pointer to task to add
 * @return 0 if successful, -1 on error
 */
int mk_sched_addReadyTask(mk_task_t *task);

/**
 * @brief Remove a task from the ready queue and update the task priority bitmap
 * 
 * @param task pointer to task to remove
 * @return 0 if successful, -1 on error
 */
int mk_sched_removeReadyTask(mk_task_t *task);

/**
 * @brief Add a task to the waiting queue and update its status
 * 
 * @param task pointer to task to add
 * @return 0 if successful, -1 on error
 */
int mk_sched_addWaitingTask(mk_task_t *task);

/**
 * @brief Remove the task at the front of the waiting list
 * 
 * @return 0 if successful, -1 on error
 */
int mk_sched_removeWaitingTask(void);

/**
 * @brief Add a task to the stopped list and update its status
 * 
 * @param task pointer to task to add
 * @return 0 if successful, -1 on error
 */
int mk_sched_addStoppedTask(mk_task_t *task);

/**
 * @brief Update mk_sched_currentTask with the next task to run
 * 
 * @return 0 if successful, -1 on error
 */
int mk_sched_getNextTask(void);

/**
 * @brief Increment the kernel tick count and check if a reschedule is necessary
 * 
 * @return 1 if a reschedule is necessary, 0 otherwise
 */
int mk_sched_incrementSystemTick(void);

/**
 * @brief Make a task wait for a specific number of ms
 * 
 * @param task task to wait
 * @param time time to wait (ms)
 */
void mk_sched_waitTask(mk_task_t *task, uint32_t time);

/**
 * @brief Yield a task's remaining cpu time and force a reschedule
 * 
 * @param task pointer to task yielding
 */
void mk_sched_yieldTask(mk_task_t *task);

/**
 * @brief Stop a task.
 * 
 * @param task pointer to task to stop
 */
void mk_sched_stopTask(mk_task_t *task);

/**
 * @brief Initialize the scheduler.
 * 
 * @return 0 if successful, -1 on error
 */
int mk_sched_init(void);

/**
 * @brief Start the scheduler. Unless an error occurs, this function
 * WILL NOT RETURN!
 * 
 * @return -1 on error
 */
int mk_sched_start(void);

#endif // MK_SCHEDULER_H_