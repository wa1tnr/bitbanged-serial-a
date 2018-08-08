/* usuart.c */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

void USART_0a_demo(void) {
	struct io_descriptor *io;
        usart_sync_get_io_descriptor(&USART_0a, &io);
        usart_sync_enable(&USART_0a);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

