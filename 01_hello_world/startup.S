.text
.code 32 /* 32-bit ARM instruction set */
.global reset, vectors_table

reset:
  ldr pc, reset_handler_addr 
  ldr pc, undefined_handler_addr 
  ldr pc, swi_handler_addr 
  ldr pc, prefetch_abort_handler_addr 
  ldr pc, data_abort_handler_addr 
  ldr pc, hypervisor_handler_addr 
  ldr pc, irq_handler_addr 
  ldr pc, fiq_handler_addr 

vectors_table:

reset_handler_addr:           .word _start
undefined_handler_addr:       .word _default_handler
swi_handler_addr:             .word _default_handler
prefetch_abort_handler_addr:  .word _default_handler 
data_abort_handler_addr:      .word _default_handler 
hypervisor_handler_addr:      .word _default_handler 
irq_handler_addr:             .word _default_handler 
fiq_handler_addr:             .word _default_handler

_default_handler:
  b .

_start: 
  /* set the new vector table */
  ldr r0, =reset
  mcr p15, 0, r0, c12, c0, 0 /* cf. ARMv7-A Ref. Manual, B4.1.156 */

  /* stack_top is defined during linking */
  ldr sp, =stack_supervisor

  bl c_entry

  /* branch on itself */
  b . 

