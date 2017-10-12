
#define MODE_USER 	0x10
#define MODE_FIQ  	0x11
#define MODE_IRQ  	0x12
#define MODE_SUPERVISOR 0x13
#define MODE_MONITOR 	0x16
#define MODE_ABORT 	    0x17
#define MODE_HYP 	    0x1A
#define MODE_UNDEFINED 	0x1B
#define MODE_SYSTEM 	0X1F

struct t_cpsr {
    unsigned int mode:5;
    unsigned int T:1;           /* Thumb */

    /* (1) exception masked (0) not masked */
    unsigned int FIQ:1;
    unsigned int IRQ:1;
    unsigned int async_abort:1;

    unsigned int E:1;           /* Endianness */
    unsigned int IT_7_2:6;
    unsigned int GE:4;
    unsigned int reserved:4;
    unsigned int J:1;           /* Jazelle */
    unsigned int IT_1_0:2;
    unsigned int Q:1;           /* Overflow or saturation */
    unsigned int V:1;           /* Overflow */
    unsigned int C:1;           /* Carry */
    unsigned int Z:1;           /* Zero */
    unsigned int N:1;           /* Negative */
};

static inline struct t_cpsr get_cpsr (void)
{
    struct t_cpsr cpsr;
  asm ("mrs %0, cpsr":"=r" (cpsr));
    return cpsr;
}

static inline void set_cpsr (struct t_cpsr cpsr)
{
  asm ("msr cpsr, %0": :"r" (cpsr));
}
