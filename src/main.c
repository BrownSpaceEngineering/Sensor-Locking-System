#include <atmel_start.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Replace the code below with your application code */
	FREERTOS_V1000_0_example();

	// TODO:
	/*
	1. How do we create a thread process
	2. How does the rtos global pq work
	3. How do we create the waitq for the gatekeeper tasks
	4. Do we need to define certain structs for different tasks (gatekeeper struct, sensor struct, etc)
	*/
}
