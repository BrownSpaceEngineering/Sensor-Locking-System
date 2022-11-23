#include "rtos_tasks.h"
#include <FreeRTOS.h>

// starts RTOS scheduler
void run_rtos()
{
    // create first init task to start RTOS and other tasks
    xTaskCreateStatic(startup_task,
                      "initializer task",
                      INIT_TASK_STACK_SIZE,
                      NULL,
                      INIT_TASK_PRIORITY,
                      init_task_stack,
                      &init_task_buffer);
}

void startup_task(void *pvParameters)
{
    // TODO: something about initializing watchdog task or something like that
    print("PVDXos starting.................................................");
    xTaskCreateStatic();

    /* Sensor Tasks */
    // TODO:

    /* Gatekeeper Tasks */
    battery_charging_task_handle = xTaskCreateStatic(battery_charging_task,
                                                     "battery charging action task",
                                                     TASK_BATTERY_CHARGING_STACK_SIZE,
                                                     NULL,
                                                     TASK_BATTERY_CHARGING_PRIORITY,
                                                     battery_charging_task_stack,
                                                     &battery_charging_task_buffer);
}