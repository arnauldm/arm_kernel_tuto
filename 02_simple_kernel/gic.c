#include "memory.h"
#include "gic.h"

volatile struct t_distributor *distributor;
volatile struct t_cpu_interface *cpu_interface;


/*
 * Enables forwarding of the corresponding interrupts from the Distributor
 * to the CPU interfaces
 */
void distributor_enable_irq (unsigned int irq)
{
    /*
     * Note: writing '0' has no effect, thus we don't have to xor the register
     * with the expected value
     */
    distributor->ICDISER[irq / 32] = (uint32_t) 1 << (irq % 32);
}


void distributor_disable_irq (unsigned int irq)
{
    distributor->ICDICER[irq / 32] = (uint32_t) 1 << (irq % 32);
}


void distributor_cpu_target (unsigned int irq, uint8_t cpu)
{
    distributor->ICDIPTR[irq] = (uint8_t) (1 << cpu);
}


/*
 * Clears the pending state of the corresponding peripheral interrupt.
 */
void distributor_clear_pending (unsigned int irq)
{
    distributor->ICDICPR[irq / 32] = (uint32_t) 1 << (irq % 32);
}


/* 
 * Enables the forwarding of pending interrupts from the Distributor to the
 * CPU interfaces 
 */
void distributor_enable (void)
{
    distributor->ICDDCR = 0x1;
}


/* 
 * Only interrupts with higher priority than the value in this register are
 * signaled to the processor.
 */
void cpu_interface_priority_filter (uint8_t priority)
{
    cpu_interface->ICCPMR |= (uint32_t) priority;
}


/*
 * Read the interrupt ID of the signaled interrupt. Acts as an acknowledge
 * for the interrupt.
 */
unsigned int cpu_interface_get_irq (void)
{
    unsigned int irq;
    irq = cpu_interface->ICCIAR & 0x1FF;
    return irq;
}


/*
 * A processor writes to EOI register to inform the CPU interface that it
 * has completed the processing of the specified interrupt.
 */
void cpu_interface_send_EOI (unsigned int irq)
{
    cpu_interface->ICCEOIR |= (irq & 0x1FF);
}


/*
 * Enable signaling of interrupts by the CPU interface to the connected
 * processor.
 */
void cpu_interface_enable (void)
{
    cpu_interface->ICCICR |= 0x1;
}


void distributor_init (void)
{
    unsigned int it_lines, i;

    /* Read the Configuration Base Address Register */
    distributor = (struct t_distributor *) (PERIPHBASE + DISTBASE);

    /* How many interrupt lines ? */
    it_lines = 32 * ((distributor->ICDICTR & 0x1F) + 1);

    /*
     * Enables forwarding of the interrupts from the Distributor
     * to the CPU interfaces
     */
    for (i = 0; i < it_lines; i++)
        distributor_enable_irq (i);

    /*
     * Set the list of CPU interfaces to which the Distributor forwards the
     * interrupt. Currently, we use only CPU interface 0.
     */
    for (i = 0; i < it_lines; i++)
        distributor_cpu_target (it_lines, 0);

    distributor_enable ();
}


void cpu_interface_init (void)
{
    /* Read the Configuration Base Address Register */
    cpu_interface = (struct t_cpu_interface *) (PERIPHBASE + CPUBASE);

    /* 
     * Signal every interrupts. Only interrupts with higher priority than the
     * value in this register (higher priority = lower value) are signaled to
     * the processor. 
     */
    cpu_interface_priority_filter (0xff);

    cpu_interface_enable ();
}


void gic_init (void)
{
    distributor_init ();
    cpu_interface_init ();
}
