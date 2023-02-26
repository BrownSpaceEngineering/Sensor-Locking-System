#ifndef RTOS_TASKS_CONFIG_H
#define RTOS_TASKS_CONFIG_H

#include <inttypes.h>

// TODO: why different stack size release vs not release in Equisatos
// 1536 = 1024 + 512
// 1792 = 1024 + 512 + 256

/************************************************************************/
/* Classes of Task Priorities                                           */
/************************************************************************/
// lowest priority is at the top
enum
{
    STATE_HANDLING_PRIORITY = 1,
};

/************************************************************************/
/* Task Properties - see below for frequencies							*/
/************************************************************************/

// TODO: why tf are these different for different tasks and how do you figure this out
#define INIT_TASK_STACK_SIZE (1536 / sizeof(portSTACK_TYPE))
#define INIT_TASK_PRIORITY (STATE_HANDLING_PRIORITY)

#define TASK_BATTERY_CHARGING_STACK_SIZE ((1024 / sizeof(portSTACK_TYPE)))
#define TASK_BATTERY_CHARGING_PRIORITY (STATE_HANDLING_PRIORITY)

#endif