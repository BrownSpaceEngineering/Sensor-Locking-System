#include <atmel_start.h>
#include "satellite_startup.h"

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Replace the code below with your application code */
	FREERTOS_V1000_0_example();

	/* Create init thread, sensor threads and gatekeeper threads*/
	run_rtos();
}

/*
TODO:
1. figure out ESSENTIAL INITIALIZATION
2. figure out xtasktick (knowing that's is a sort of blocking until time expire)
3. FIgure out i2c header packet thing
4. FIgure out spi header packet thing (read, write)
5. FInish setup for sample_task_one
*/