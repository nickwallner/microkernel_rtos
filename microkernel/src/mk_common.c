#include "mk_common.h"

/* this is the idle task, it is placed on the cpu
if no other task is currently available */
void mk_idleTask(void)
{
    while (1) { }
}