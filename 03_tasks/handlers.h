
struct t_regs {
    uint32_t r[13];             /* r0 - r12 */
    uint32_t cp;
    uint32_t cpsr;
};

typedef void (*t_irq_handler) (void);

extern void set_irq_handler (unsigned int, t_irq_handler);
