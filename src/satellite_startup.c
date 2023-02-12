#include "satellite_startup.h"
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
    print("PVDXos starting..");
    xTaskCreateStatic();

    //"Voltage do shit -Siddharth 2023"

    /************************************************************************/
    /* Mutexes */
    /************************************************************************/

    /*
     XSemaphoreCreateMutexStatic takes in the address of a StaticSemaphore_t variable and returns a Semaphore handle
     SemaphoreHandle was declared in rtos_tasks.h file since that was what EQUISAT did
     However, in EQUISAT, the StaticSemaphore_t was declared in a array of Mutex Addressses but do we need that? since we only need 3 mutexes
     and they needed 10+
    */
    spi_mutex = xSemaphoreCreateMutexStatic(&spi_mutex_d);
    i2c_mutex = xSemaphoreCreateMutexStatic(&i2c_mutex_d);

    // TODO(siddharth): figure out this section
    /************************************************************************/
    /* ESSENTIAL INITIALIZATION                                             */
    /************************************************************************/
    // read state from MRAM for first time
    // this initializes the error equistacks, so make sure no errors
    // are logged before this (they shouldn't be before RTOS is started...)
    configure_state_from_reboot();

    // function in global to init things that use RTOS
    // (MUST be done after config state from reboot)
    global_init_post_rtos();

    // populate task_handles array and setup constants
    pre_init_rtos_tasks();

    /************************************************************************/
    /* Sensor Tasks */
    /************************************************************************/

    // Create a new task and add it to the list of tasks that are ready to run
    TaskHandle_t xTaskCreateStatic(TaskFunction_t pxTaskCode,
                                   const char *const pcName,
                                   const uint32_t ulStackDepth,
                                   void *const pvParameters,
                                   UBaseType_t uxPriority,
                                   StackType_t *const puxStackBuffer,
                                   StaticTask_t *const pxTaskBuffer);

    // TODO:
    sample_tast_one_handle = xTaskCreateStatic(sample_task_one,
                                               "battery charging action task",
                                               TASK_BATTERY_CHARGING_STACK_SIZE,
                                               NULL,
                                               TASK_BATTERY_CHARGING_PRIORITY,
                                               sample_tast_one_stack,
                                               &sample_tast_one_buffer);
}