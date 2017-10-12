#include "gic.h"
#include "global_timer.h"
#include "lib.h"
#include "handlers.h"

extern char _task0_start;
extern char _task0_end;
#define TASK0_ADDR 0x60010000


void global_timer_handler (void)
{
    static int counter = 0;
    printk (".");
    counter++;
    global_timer_clear_event ();
}


void __attribute__ ((noreturn)) c_entry ()
{
    printk ("hello, world!\n");

    memcpy ((char *) TASK0_ADDR, &_task0_start,
            (char *) &_task0_end - (char *) &_task0_start);

    gic_init ();

    global_timer_init ();
    global_timer_auto_increment (0x04000000);
    set_irq_handler (27, global_timer_handler);

    /* Enable IRQ and FIQ and enter in user mode */
    asm volatile
     ("cpsie if, #0x10\n"
      "mov pc, %[task0]"::[task0] "r" (TASK0_ADDR):"memory", "cc");

    /* We should never enter here */
    printk ("BUG! :-(\n");
    while (1);
}
