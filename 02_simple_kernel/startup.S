.text
.code 32 /* 32-bit ARM instruction set */
.global reset, vectors_table

/*
 * This file is designed to be generic, and should work for any ARM-based MCU
 * without modifications
 */

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
swi_handler_addr:             .word asm_swi_handler
prefetch_abort_handler_addr:  .word _default_handler 
data_abort_handler_addr:      .word _default_handler 
hypervisor_handler_addr:      .word _default_handler 
irq_handler_addr:             .word c_irq_handler 
fiq_handler_addr:             .word _default_handler

_default_handler:
  b .

_start: 
  /* set the new vector table */
  ldr r0, =reset
  mcr p15, 0, r0, c12, c0, 0 /* cf. ARMv7-A Ref. Manual, B4.1.156 */

  /* processor core starts in supervisor mode */
  ldr sp, =stack_supervisor

  /* set FIQ stack */
  cps #0x11
  ldr sp,=stack_fiq

  /* set IRQ stack */
  cps #0x12
  ldr sp,=stack_irq

  /* set SVM stack */
  cps #0x16
  ldr sp,=stack_monitor


  bl c_entry

  /* branch on itself */
  b . 

asm_swi_handler:
  /* Store registers */
  push {r0-r12,lr}

  /* Calculate address of SVC instruction and load it into R0 */
  ldr r0,[lr,#-4]   

  /* Mask off top 8 bits of instruction to give SVC number */
  bic r0,r0,#0Xff000000

  /* Use value in R0 to determine which SVC routine to execute */
  bl c_swi_handler

  /* Restore registers and return */
  ldm sp!, {r0-r12,pc}^ 

