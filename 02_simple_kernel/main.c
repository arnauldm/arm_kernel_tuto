#include "gic.h"
#include "timer.h"
#include "lib.h"
#include "handlers.h"


void gtimer_handler (void)
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
    global_timer_auto_increment (0x01000000);
    set_irq_handler (27, gtimer_handler);

    gic_enable ();

    asm volatile ("svc 0x42");

    while (1);
}
