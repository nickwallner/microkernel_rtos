#ifndef MK_COMMON_H_
#define MK_COMMON_H_

#include <stddef.h>
#include <stdint.h>

#include "mk_config.h"
#include "mk_queue.h"

/****************/
/* Kernel Types */
/****************/

/* kernel queue type */
typedef Queue_t             mk_queue_t;

/* task control block type */
typedef struct mk_task      mk_task_t;

/* types for task control block members */
typedef uint8_t             mk_taskPriority_t;
typedef uint16_t            mk_taskID_t;
typedef enum mk_taskState   mk_taskState_t;
typedef int16_t             mk_taskHandle_t;

enum mk_taskState
{
    READY       = 0,
    WAITING     = 1,
    STOPPED     = 2
};

struct mk_task
{
    void                *stackPtr;  // current stack pointer
    mk_taskPriority_t   priority;   // task priority
    mk_taskID_t         taskID;     // task id
    mk_taskState_t      state;      // task state
    uint32_t            timeSlice;  // time slice for this task (ms)
    uint32_t            timeLeft;   // remaining cpu time for the task (ms)
    uint32_t            wakeTime;   // the kernel tick count when this task will wake up
    mk_taskHandle_t     taskHandle; // task handle (index in task pool)
    mk_taskHandle_t     next;       // index in the task pool of the next task in the queue
    mk_taskHandle_t     prev;       // index in the task pool of the prev task in the queue
};

/******************/
/* Kernel Globals */
/******************/

/* task that is currently on the cpu */
extern mk_task_t    *_mk_currentTask;

/* pool of available/used tasks */
extern mk_task_t    _mk_taskPool[];

/* current kernel tick count */
extern uint32_t     _mk_kernelTickCount;

/* current available task id */
extern mk_taskID_t  _mk_currentTaskID;

/* kernel idle task */
void mk_idleTask(void);

#endif // MK_COMMON_H_