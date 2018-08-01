/* usuart.c */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using USUART_5 to write "Hello World" using the IO abstraction.
 */
void USUART_5_demo(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_5, &io);
	usart_sync_enable(&USART_5);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

