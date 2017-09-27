#include <stdint.h>

#define UART0_ADDR  0x10009000  /* cf. [MOTHERBOARD] p. 4-6 */

struct t_uart {                 /* cf. [UART] p.49 */
    uint32_t DR;                /* Data */
    uint32_t RSR;               /* Status / Clear Error */
    uint32_t reserved0[4];
    uint32_t FR;                /* Flag */
    uint32_t reserved1;
    uint32_t ILPR;              /* IrDA Low-Power Counter */
    uint32_t IBRD;              /* Integer Baud Rate */
    uint32_t FBRD;              /* Fractional Baud Rate */
    uint32_t LCR_H;             /* Line Control */
    uint32_t LCR;               /* Control */
    uint32_t IFLS;              /* Interrupt FIFO Level */
    uint32_t IMSC;              /* Interrupt Mask Set/Clear */
    uint32_t RIS;               /* Raw Interrupt Status */
    uint32_t MIS;               /* Masked Interrupt Status */
    uint32_t ICR;               /* Interrupt Clear */
    uint32_t DMACR;             /* DMA Control */
};

struct t_uart *const uart = (struct t_uart *) UART0_ADDR;


void serial_out (char *s)
{
    while (*s) {
        uart->DR = (uint32_t) * s;
        s++;
    }
}

void c_entry ()
{
    serial_out ("hello, world!\n");
    while (1);
}
