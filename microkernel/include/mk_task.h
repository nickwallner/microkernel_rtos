#ifndef MK_TASKS_H_
#define MK_TASKS_H_

#include "mk_common.h"

/**
 * @brief Initialize the kernel tasks.
 * 
 */
void mk_task_init(void);

/**
 * @brief Get a pointer to a task's task control block given its ID.
 * 
 * @param taskID The ID of the task to search for
 * @return Pointer to the TCB if found and active, NULL otherwise
 */
mk_task_t *mk_task_getTaskByID(mk_taskID_t taskID);

#endif // MK_TASKS_H_