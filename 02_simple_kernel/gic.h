#include <stdint.h>

/*
 * References: [MPCORE-A9] and [GIC]
 */

typedef uint32_t __unused__;

/* 
 * Distributor registers (cf. [MPCORE-A9] p. 3-5) 
 * Offset are relative to the PERIPHBASE value + 0x1000 (cf. [MPCORE-A9] p.
 * 1-7)
 */
#define DISTBASE 0x1000

struct t_distributor {
    uint32_t ICDDCR;            /* Distributor Control */
    uint32_t ICDICTR;           /* Interrupt Controller Type (RO) */
    uint32_t ICDIIDR;           /* Distributor Implementer Identification (RO) */
    __unused__ reserved_1[29];
    uint32_t ICDISR[8];         /* Interrupt Security Registers */
    __unused__ reserved_2[24];
    uint32_t ICDISER[8];        /* Interrupt Set-Enable Registers */
    __unused__ reserved_3[24];
    uint32_t ICDICER[8];        /* Interrupt Clear-Enable Registers */
    __unused__ reserved_4[24];
    uint32_t ICDISPR[32];       /* Interrupt Set-Pending Registers */
    uint32_t ICDICPR[8];        /* Interrupt Clear-Pending Registers */
    __unused__ reserved_5[24];
    uint32_t ICDABR[8];         /* Active Bit registers (RO) */
    __unused__ reserved_6[56];
    uint32_t ICDIPR[64];        /* Interrupt Priority Registers */
    __unused__ reserved_7[192];
    uint32_t ICDIPTR[64];       /* Interrupt Processor Targets Registers */
    __unused__ reserved_8[192];
    uint32_t ICDICFR[64];       /* Interrupt Configuration Registers */
    uint32_t ICPPISR;           /* Private Peripheral Interrupt (PPI) Status */
    uint32_t ICSPISR[7];        /* Shared Peripheral Interrupt (SPI) Status */
    __unused__ reserved_9[120];
    uint32_t ICDSGIR;           /* Software Generated Interrupt */
};

/* 
 * Interrupt interface registers (cf. [MPCORE-A9] p. 3-13) 
 * Offset are relative to the CPU interface base address
 * that is PERIPHBASE + 0x100. (cf. [MPCORE-A9] p. 1-7)
 */
#define CPUBASE 0x100

struct t_cpu_interface {
    uint32_t ICCICR;            /* CPU Interface Control */
    uint32_t ICCPMR;            /* Interrupt Priority Mask */
    uint32_t ICCBPR;            /* Binary Point */
    uint32_t ICCIAR;            /* Interrupt Acknowledge */
    uint32_t ICCEOIR;           /* End Of Interrupt */
    uint32_t ICCRPR;            /* Running Priority */
    uint32_t ICCHPIR;           /* Highest Pending Interrupt */
    uint32_t ICCABPR;           /* Aliased Non-secure Binary Point */
    uint32_t reserved[55];
    uint32_t ICCIDR;            /* CPU Interface Implementer Identification */
};

/* Read Configuration Base Address Register */
static inline uint32_t get_periphbase (void)
{
    uint32_t periphbase;
  asm ("mrc p15, 4, %0, c15, c0, 0":"=r" (periphbase));
    return periphbase;
}
