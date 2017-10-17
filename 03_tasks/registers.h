
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
    uint32_t mode:5;
    uint32_t T:1;           /* Thumb */

    /* (1) exception masked (0) not masked */
    uint32_t FIQ:1;
    uint32_t IRQ:1;
    uint32_t async_abort:1;

    uint32_t E:1;           /* Endianness */
    uint32_t IT_7_2:6;
    uint32_t GE:4;
    uint32_t reserved:4;
    uint32_t J:1;           /* Jazelle */
    uint32_t IT_1_0:2;
    uint32_t Q:1;           /* Overflow or saturation */
    uint32_t V:1;           /* Overflow */
    uint32_t C:1;           /* Carry */
    uint32_t Z:1;           /* Zero */
    uint32_t N:1;           /* Negative */
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
