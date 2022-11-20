#ifndef RTOS_TASKS_CONFIG_H
#define RTOS_TASKS_CONFIG_H

// TODO: why different stack size release vs not release in Equisatos
// 1536 = 1024 + 512
// 1792 = 1024 + 512 + 256
#define TASK_INIT_STACK_SIZE (1536 / sizeof(portSTACK_TYPE))

#endif