/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using USART_0a to write "Hello World" using the IO abstraction.
 */
void USART_0a_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_0a, &io);
	usart_sync_enable(&USART_0a);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

void delay_example(void)
{
	delay_ms(5000);
}
