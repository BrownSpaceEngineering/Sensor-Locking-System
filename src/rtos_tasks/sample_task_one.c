#include "src/satellite_startup.h"

void sample_task_one(void *pvParameters)
{
    print("\n\nstarting sample task!\n");

    // initialize xNextWakeTime onces
    init_task_state(sample_task_one); // suspend or run on boot (ALWAYS RUN!)

    // Release the semaphore xSemaphore
    xSemaphoreGive(_spi_mutex);

    // Lock the semaphore xSemaphore. If already occupied, wait xTicksToWait
    // use portTICK_PERIOD_MS to convert ticks to real-time seconds
    xSemaphoreTake(_spi_mutex, TickType_t xTicksToWait);

    uint8_t iter_count = 0;
    while (true)
    {
        // report to watchdog
        report_task_running(sample_task_one);

        print("entering battery task!\n");
        if (iter_count % BAT_CHARGING_ITERS_UNTIL_FULL == 0 || get_sat_state_wrapped() == LOW_POWER)
        {
            // the core battery logic -- a separate function to make it easier to
            // unit test
            // there's an update to should_deploy_antenna within battery logic
            battery_logic();
            iter_count = 0;
        }
        else
        {
            print("not running the full logic yet: iter at %d\n", iter_count);
            update_should_deploy_antenna(false);
        }

        iter_count++;
        vTaskDelayUntil(&prev_wake_time, sample_task_one_FREQ / portTICK_PERIOD_MS);
    }

    // delete this task if it ever breaks out
    vTaskDelete(NULL);
}
