#include <stdint.h>

/*
 * Reference: [UART] p.49
 */

struct t_uart {
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

extern void serial_out (char);
