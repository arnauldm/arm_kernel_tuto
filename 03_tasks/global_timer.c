#include "memory.h"
#include "global_timer.h"
#include "lib.h"

volatile struct t_global_timer *global_timer;


void global_timer_clear_event (void)
{
    global_timer->it_status |= 0x1;
}

void global_timer_init (void)
{
    global_timer = (struct t_global_timer *) (PERIPHBASE + 0x200);
    global_timer->ctrl |= TIMER_ENABLE;
}

void global_timer_auto_increment (uint32_t period)
{
    global_timer->ctrl &= ~TIMER_ENABLE;
    global_timer->ctrl &= ~COMP_ENABLE;
    global_timer->auto_incr = period;
    global_timer->ctrl |= COMP_ENABLE;
    global_timer->ctrl |= IRQ_ENABLE;
    global_timer->ctrl |= AUTO_INCR_ENABLE;
    global_timer->ctrl |= TIMER_ENABLE;
}
