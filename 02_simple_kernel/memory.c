#include <stdint.h>

/* 
 * Read the Configuration Base Address Register 
 * [CORTEX-A9] ch. 4.3.25, p. 4-97
 * Note: on [VEXPRESS-A9], p. 3-5, the address is set at 0x1E000000
 */
uint32_t get_periphbase (void)
{
    uint32_t periphbase;
  asm ("mrc p15, 4, %0, c15, c0, 0":"=r" (periphbase));
    return periphbase;
}
