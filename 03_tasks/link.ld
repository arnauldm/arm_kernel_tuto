ENTRY(reset)

MEMORY
{
	/* 
	 * QEMU `-kernel` option loads a binary file (usually a Linux kernel)
	 * inside the system memory starting at address 0x00010000. 
	 */
	RAM (xrw) : ORIGIN = 0x60000000, LENGTH = 128M
}

SECTIONS
{
	.startup : { *startup.o(.text) } >RAM
	.text : { *(.text) } >RAM
	.data : { *(.data) } >RAM
	.bss : { *(.bss) *(COMMON) } >RAM

	. = ALIGN(8);
	. = . + 0x1000; /* 4kB of stack memory */
	stack_supervisor = .;

	. = . + 0x1000; /* 4kB of stack memory */
	stack_fiq = .;

	. = . + 0x1000; /* 4kB of stack memory */
	stack_irq = .;

	. = . + 0x1000; /* 4kB of stack memory */
	stack_monitor = .;

	.task0 : { 
		_task0_start = .;
		*task0.o 
		_task0_end = .;
	} >RAM

}

