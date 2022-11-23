#ifndef RTOS_TASKS_H
#define RTOS_TASKS_H

#include <FreeRTOS.h>

/************************************************************************/
/* Function Signatures                                                  */
/************************************************************************/
void run_rtos();
void startup_task(void *pvParameteres);

/************************************************************************/
/* Classes of Task Priorities                                           */
/************************************************************************/
// lowest priority is at the top
enum
{
    STATE_HANDLING_PRIORITY = 1,
};

// TODO: why different stack size release vs not release in Equisatos
// 1536 = 1024 + 512
// 1792 = 1024 + 512 + 256

/************************************************************************/
/* Task Properties - see below for frequencies							*/
/************************************************************************/

#define INIT_TASK_STACK_SIZE (1536 / sizeof(portSTACK_TYPE))
#define INIT_TASK_PRIORITY (STATE_HANDLING_PRIORITY)

/******************************************************************************/
/* Global static memory allocated for tasks; stack and data structure holding */
/******************************************************************************/

StaticTask_t init_task_buffer;
StackType_t init_task_stack[INIT_TASK_STACK_SIZE];

TaskHandle_t spi_gatekeeper_task;

#endif