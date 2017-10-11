#include "gic.h"
#include "global_timer.h"
#include "lib.h"
#include "handlers.h"


void global_timer_handler (void)
{
    static int counter = 0;
    printk ("[%d]\n", ++counter);
    global_timer_clear_event ();
}


void c_entry ()
{
    printk ("hello, world!\n");

    gic_init ();

    global_timer_init ();
    global_timer_auto_increment (0x04000000);
    set_irq_handler (27, global_timer_handler);

    /* Enable IRQ and FIQ */
    asm volatile ("cpsie if":::"memory", "cc");

    /* Testing software interrupt */
    asm volatile ("svc 0x42");

    while (1);
}
