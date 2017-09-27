#include <stdint.h>
#include <stdarg.h>
#include "registers.h"
#include "gic.h"
#include "timer.h"
#include "lib.h"


volatile struct t_distributor *distributor;
volatile struct t_cpu_interface *cpu_interface;
volatile struct t_global_timer *global_timer;


void c_swi_handler (uint32_t num)
{
    printk ("svc %x\n", num);
}

void __attribute__ ((interrupt ("IRQ"))) c_irq_handler (void)
{
    int irq;
    static unsigned int counter = 0;

    /* Disable IRQs */
    asm volatile ("cpsid i":::"memory", "cc");

    /*
     * Read the interrupt ID of the signaled interrupt. Acts as an acknowledge
     * for the interrupt.
     */

    irq = cpu_interface->ICCIAR & 0x1FF;
    printk ("irq %d (%d)\n", irq, ++counter);

    /*
     * Clears the pending state of the corresponding peripheral interrupt.
     */

    distributor->ICDICPR[irq / 32] = 1 << (irq % 32);

    /*
     * A processor writes to EOI register to inform the CPU interface that it
     * has completed the processing of the specified interrupt.
     */

    cpu_interface->ICCEOIR = irq;

    if (irq == 27) {            /* Global timer */
        global_timer->intr_status |= 0x1;
    }

    asm volatile ("cpsie i":::"memory", "cc");
}

void __attribute__ ((interrupt ("FIQ"))) c_fiq_handler (void)
{
    printk ("fiq\n");
}

void c_entry ()
{
    struct t_cpsr cpsr;
    uint32_t periphbase;
    int intr_lines;
    int i;

    printk ("hello, world!\n");

    /* 
     * Read the Configuration Base Address Register 
     */

    periphbase = get_periphbase ();

    distributor = (struct t_distributor *) (periphbase + DISTBASE);
    cpu_interface = (struct t_cpu_interface *) (periphbase + CPUBASE);

    /* IT lines number */
    intr_lines = 32 * ((distributor->ICDICTR & 0x1F) + 1);

    /*
     * Enables forwarding of the corresponding interrupts from the Distributor
     * to the CPU interfaces
     */

    for (i = 0; i < (intr_lines / 32) + ((intr_lines % 32) ? 1 : 0); i++)
        distributor->ICDISER[i] = 0xFFFFFFFF;

    /*
     * Set the list of CPU interfaces to which the Distributor forwards the
     * interrupt. Currently, we use only CPU interface 0.
     */
    for (i = 0;
         i < (intr_lines / 32) + ((intr_lines % 32 > 0) ? 1 : 0); i++)
        distributor->ICDIPTR[i] = 0x01010101;

    /* 
     * Enables the forwarding of pending interrupts from the Distributor to the
     * CPU interfaces 
     */

    distributor->ICDDCR = 0x1;

    /* 
     * Only interrupts with higher priority than the value in this register are
     * signaled to the processor.
     */

    cpu_interface->ICCPMR = 0xFF;

    /* 
     * Enables the signaling of interrupts by the CPU interface to the
     * connected processor 
     */

    cpu_interface->ICCICR = 0x1;

    /* Enable IRQ and FIQ */

    cpsr = get_cpsr ();
    cpsr.IRQ = 0;
    cpsr.FIQ = 0;
    set_cpsr (cpsr);

    asm volatile ("cpsie if":::"memory", "cc");

    /* 
     * Enable Global Timer interrupts by writing to the
     * Global Timer Control Register
     */

    global_timer = (struct t_global_timer *) (periphbase + 0x200);
    global_timer->ctrl &= ~TIMER_ENABLE;
    global_timer->ctrl &= ~COMP_ENABLE;
    global_timer->auto_incr = 0x01000000;
    global_timer->ctrl |= COMP_ENABLE;
    global_timer->ctrl |= IRQ_ENABLE;
    global_timer->ctrl |= AUTO_INCR_ENABLE;
    global_timer->ctrl |= TIMER_ENABLE;

    asm volatile ("svc 0x42");

    while (1);
}
