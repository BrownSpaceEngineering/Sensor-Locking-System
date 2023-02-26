#include "satellite_startup.h"
#include "rtos_task_config.h"
#include <FreeRTOS.h>
#include "semphr.h"

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
    // StaticSemaphore_t _attitude_equistack_mutex_d;
    // int _attitude_equistack_mutex = xSemaphoreCreateMutexStatic(&_attitude_equistack_mutex_d);

    // // Release the semaphore xSemaphore
    // SemaphoreHandle_t xSemaphore;
    // xSemaphoreGive(xSemaphore);
    // // Lock the semaphore xSemaphore. If already occupied, wait xTicksToWait
    // // use portTICK_PERIOD_MS to convert ticks to real-time seconds
    // xSemaphoreTake(SemaphoreHandle_t xSemaphore, TickType_t xTicksToWait);
    StaticSemaphore_t _attitude_equistack_mutex_d;
    SemaphoreHandle_t _attitude_equistack_mutex = xSemaphoreCreateMutexStatic(&_attitude_equistack_mutex_d);

    // Lock the semaphore _attitude_equistack_mutex. If already occupied, wait indefinitely
    if (xSemaphoreTake(_attitude_equistack_mutex, portMAX_DELAY) == pdTRUE)
    {
        // Semaphore taken successfully
        // Do some critical section work /// what critical work do we want to do in here?
        // ...

        // Release the semaphore _attitude_equistack_mutex
        xSemaphoreGive(_attitude_equistack_mutex);
    }

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
    // https://www.freertos.org/xTaskCreateStatic.html
    TaskHandle_t xTaskCreateStatic(TaskFunction_t pxTaskCode,
                                   const char *const pcName,
                                   const uint32_t ulStackDepth,
                                   void *const pvParameters,
                                   UBaseType_t uxPriority,
                                   StackType_t *const puxStackBuffer,
                                   StaticTask_t *const pxTaskBuffer);

    // TODO:
    battery_charging_task_handle = xTaskCreateStatic(battery_charging_task,
                                                     "battery charging action task",
                                                     TASK_BATTERY_CHARGING_STACK_SIZE,
                                                     NULL,
                                                     TASK_BATTERY_CHARGING_PRIORITY,
                                                     battery_charging_task_stack,
                                                     &battery_charging_task_buffer);
}