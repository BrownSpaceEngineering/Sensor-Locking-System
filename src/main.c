#include <atmel_start.h>
#include "rtos_tasks_config.h"

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Replace the code below with your application code */
	FREERTOS_V1000_0_example();

	// TODO:
	/*
	1. How do we create a thread process
	2. How does the FreeRTos global pq work
	3. How do we create the waitq for the gatekeeper tasks
	4. Do we need to define certain structs for different tasks (gatekeeper struct, sensor struct, etc)
	*/

	// create first init task to start RTOS and other tasks
	xTaskCreateStatic(startup_task,
					  "initializer task",
					  TASK_INIT_STACK_SIZE,
					  NULL,
					  TASK_INIT_PRIORITY,
					  init_task_stack,
					  &init_task_buffer);
}

void startup_task(void *pvParameters)
{
	print("PVDXos starting.................................................");
}