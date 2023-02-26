#ifndef SATELLITE_STARTUP_H
#define SATELLITE_STARTUP_H

#include <FreeRTOS.h>
#include "task.h"
#include "semphr.h"
#include "rtos_task_config.h"

/************************************************************************/
/* Function Signatures                                                  */
/************************************************************************/
void run_rtos();
void startup_task(void *pvParameteres);

/******************************************************************************/
/* Global static memory allocated for tasks; stack and data structure holding */
/******************************************************************************/

StaticTask_t init_task_buffer;
StackType_t init_task_stack[INIT_TASK_STACK_SIZE];

StaticTask_t sample_task_one_buffer;
StackType_t sample_task_one_stack[TASK_BATTERY_CHARGING_STACK_SIZE];

// Sephamore Handles
StaticSemaphore_t spi_mutex_d;
SemaphoreHandle_t spi_mutex;
StaticSemaphore_t i2c_mutex_d;
SemaphoreHandle_t i2c_mutex;

// Tasks
TaskHandle_t sample_tast_one_handle;

#define SPI_MUTEX_WAIT_TIME_TICKS (10000 / portTICK_PERIOD_MS)
#define I2C_MUTEX_WAIT_TIME_TICKS (10000 / portTICK_PERIOD_MS)
#endif