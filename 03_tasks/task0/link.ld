ENTRY(c_entry)

MEMORY
{
	RAM (xrw) : ORIGIN = 0x60010000, LENGTH = 64K
}

SECTIONS
{
	.text : { *(.text) }
	.data : { *(.text) }
	.bss : { *(.text) }
}
