#include <stdint.h>
#include "memory.h"
#include "uart.h"

struct t_uart *const uart = (struct t_uart *) UART0_ADDR;

void serial_out (char c)
{
    uart->DR = (uint32_t) c;
}
