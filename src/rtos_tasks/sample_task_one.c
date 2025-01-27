#include "src/satellite_startup.h"
#include "projdefs.h"

void sample_task_one(void *pvParameters)
{
    print("\n\nstarting sample task!\n");

    // Release the semaphore xSemaphore
    // xSemaphoreGive(spi_mutex);

    // Lock the semaphore xSemaphore. If already occupied, wait xTicksToWait
    // use portTICK_PERIOD_MS to convert ticks to real-time seconds

    // xSemaphoreTake(spi_mutex, TickType_t xTicksToWait);

    if (spi_mutex != NULL)
    {
        /* See if we can obtain the semaphore.  If the semaphore is not
        available wait 10 ticks to see if it becomes free. */
        if (xSemaphoreTake(spi_mutex, (TickType_t)SPI_MUTEX_WAIT_TIME_TICKS) == pdTRUE)
        {
            /* We were able to obtain the semaphore and can now access the
            shared resource. */

            /* ... */

            /* We have finished accessing the shared resource.  Release the
            semaphore. */
            xSemaphoreGive(spi_mutex);
        }
        else
        {
            /* We could not obtain the semaphore and can therefore not access
            the shared resource safely. */
        }
    }
}

// void sample_task_one(void *pvParameters)
// {
//     print("\n\nstarting sample task!\n");

//     // initialize xNextWakeTime onces
//     init_task_state(sample_task_one); // suspend or run on boot (ALWAYS RUN!)

//     // Release the semaphore xSemaphore
//     xSemaphoreGive(spi_mutex);

//     // Lock the semaphore xSemaphore. If already occupied, wait xTicksToWait
//     // use portTICK_PERIOD_MS to convert ticks to real-time seconds

//     xSemaphoreTake(spi_mutex, TickType_t xTicksToWait);

//     uint8_t iter_count = 0;
//     while (1)
//     {
//         // report to watchdog
//         report_task_running(sample_task_one);

//         print("entering battery task!\n");
//         if (iter_count % BAT_CHARGING_ITERS_UNTIL_FULL == 0 || get_sat_state_wrapped() == LOW_POWER)
//         {
//             // the core battery logic -- a separate function to make it easier to
//             // unit test
//             // there's an update to should_deploy_antenna within battery logic
//             battery_logic();
//             iter_count = 0;
//         }
//         else
//         {
//             print("not running the full logic yet: iter at %d\n", iter_count);
//             update_should_deploy_antenna(false);
//         }

//         iter_count++;
//         vTaskDelayUntil(&prev_wake_time, sample_task_one_FREQ / portTICK_PERIOD_MS);
//     }

//     // delete this task if it ever breaks out
//     vTaskDelete(NULL);
// }
