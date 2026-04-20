#include "mk_common.h"

// This file contains the definitions for all global variables declared in mk_common.h

mk_task_t           *_mk_currentTask = NULL;
uint32_t            _mk_kernelTickCount = 0;
mk_taskID_t         _mk_currentTaskID = 1;
mk_task_t           _mk_taskPool[MK_CONFIG_MAX_TASKS + 1];
