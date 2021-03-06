
# References

[VEXPRESS-A9] *ARM CoreTile Express A9×4 Cortex-A9 MPCore (V2P-CA9) Technical Reference Manual*
[MOTHERBOARD] *ARM Motherboard Express µATX*
[UART] *PrimeCell UART (PL011) Technical Reference Manual.*
[MPCORE-A9] *Cortex-A9 MPCore Technical Reference Manual*
[GIC] *ARM Generic Interrupt Controller*

# Where is mapped the UART ?

* Document [VEXPRESS-A9] describes the overall architecture of the *versatile
  express cortex-a9* development card. Page 3-3 describes the daughterboard
  memory map. Is the serial port on *SMB CS7* (mapped on 0x10000000) or on the
  *on-chip peripheral* part ?  Page 3-5 describes the on-chip peripheral and
  there's no uart here.  

* Motherboard peripherals are described on [MOTHERBOARD]. Page 4-3 and 4-4
  contains the memory map of the ARM legacy peripherals. Page 4-4 gives the
  following information:

	Peripheral: UART0 
	Interface logic: ARM PL011 
	SMB chip select: CS7 
	Address offset: 0x00009000-0x00009FFF 

* Page 4-3 shows that *SMB CS7* is mapped at 0x10000000. UART interface is
  described page 4-37 of [MOTHERBOARD] and in [UART] documentation.

* Registers are described page 3-3 in [UART] documentation.


