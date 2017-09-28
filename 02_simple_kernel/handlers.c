#include "lib.h"
#include "gic.h"
#include "handlers.h"


t_irq_handler irq_handler[MAXIRQ];


void c_swi_handler (uint32_t num)
{
    printk ("svc %x\n", num);
}


/* 
 * Note: this __attribute__ cannot handle nested interrupts 
 * ARM Ltd. recommends using SYSTEM mode while programming reentrant interrupt handlers
 */
void __attribute__ ((interrupt ("IRQ"))) c_irq_handler (void)
{
    int irq;

    /* Disable IRQs */
    asm volatile ("cpsid i":::"memory", "cc");

    /*
     * Read the interrupt ID of the signaled interrupt. Acts as an acknowledge
     * for the interrupt.
     */

    irq = cpu_interface_get_irq ();
    printk ("irq %d\n", irq);
    irq_handler[irq] ();

    /*
     * Clears the pending state of the corresponding peripheral interrupt.
     */

    distributor_clear_pending (irq);

    /*
     * A processor writes to EOI register to inform the CPU interface that it
     * has completed the processing of the specified interrupt.
     */

    cpu_interface_send_EOI (irq);

    /* Enable IRQs */
    asm volatile ("cpsie i":::"memory", "cc");
}


void set_irq_handler (int irq, t_irq_handler fn)
{
    irq_handler[irq] = fn;
}


void default_irq_handler (void)
{
    /* nop */
}


void irq_handler_init (void)
{
    for (int i = 0; i < MAXIRQ; i++)
        set_irq_handler (i, &default_irq_handler);
}
