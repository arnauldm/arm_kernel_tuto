#include <stdint.h>

struct t_global_timer {
    uint32_t low_counter;
    uint32_t hi_counter;
    uint32_t ctrl;
    uint32_t it_status;
    uint32_t low_comparator;
    uint32_t hi_comparator;
    uint32_t auto_incr;
};

#define TIMER_ENABLE        0x1
#define COMP_ENABLE         0x2
#define IRQ_ENABLE          0x4
#define AUTO_INCR_ENABLE    0x8

extern void global_timer_init (void);
extern void global_timer_auto_increment (uint32_t);
extern void global_timer_clear_event (void);
