#ifndef MK_MEM_H_
#define MK_MEM_H_

#include "mk_common.h"
#include "port.h"

/**
 * @brief Initialize the kernel stack and idle task stack.
 * 
 */
void mk_mem_init(void);

/**
 * @brief Initialize a task's stack frame
 * 
 * @param task pointer to task whose stack is being initialized
 * @param size desired size of the task's stack (bytes)
 * @param entry pointer to the entry address of the task
 * @param arg pointer to the argument to be passed to task, or NULL for no argument
 * @return 0 if successful, -1 on error
 */
int mk_mem_initTaskStackFrame(mk_task_t *task, size_t size, void *entry, void *arg);

#endif // MK_MEM_H_