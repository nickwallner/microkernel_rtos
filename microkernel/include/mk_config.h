#ifndef MK_CONFIG_H_
#define MK_CONFIG_H_

/* system operating frequency (hz) */
#define MK_CONFIG_SYS_FREQ_HZ 16000000

/* system tick rate (hz) */
#define MK_CONFIG_SYS_TICK_RATE_HZ 1000

/* maximum number of tasks, limited only by available memory */
#define MK_CONFIG_MAX_TASKS 32

/* the number of available priority levels for tasks,
max priority levels is 32 */
#define MK_CONFIG_PRIORITY_LEVELS 10

/* the time slice (quantum) for tasks (ms) */
#define MK_CONFIG_TASK_TIME_SLICE_MS 10

/* the size of the kernel stack (bytes) */
#define MK_CONFIG_KERNEL_STACK_SIZE 512

#endif // MK_CONFIG_H_