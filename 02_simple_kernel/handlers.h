
typedef void (*t_irq_handler) (void);

extern void set_irq_handler (unsigned int, t_irq_handler);
