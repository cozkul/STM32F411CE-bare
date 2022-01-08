@ Directives: parameters/instruction for assembler
.syntax unified
.cpu cortex-m4
.fpu fpv4-sp-d16
.thumb

.word _sdata
.word _edata

.word _sbss
.word _ebss

.global vectors

.section .vector_table,"a",%progbits
    .type vectors, %object
    .size vectors, .-vectors

@ section 10.2 pg 201
@ always populate the vector table addresses
vectors:
	.word	_estack
	.word	Reset_Handler
	.word	NMI_Handler
	.word	HardFault_Handler
	.word	MemManage_Handler
	.word	BusFault_Handler
	.word	UsageFault_Handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	SVC_Handler
	.word	DebugMon_Handler
	.word	0
	.word	PendSV_Handler
	.word	SysTick_Handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0

    .weak	NMI_Handler
	.thumb_set NMI_Handler,Default_Handler

  	.weak	HardFault_Handler
	.thumb_set HardFault_Handler,Default_Handler

  	.weak	MemManage_Handler
	.thumb_set MemManage_Handler,Default_Handler

  	.weak	BusFault_Handler
	.thumb_set BusFault_Handler,Default_Handler

	.weak	UsageFault_Handler
	.thumb_set UsageFault_Handler,Default_Handler

	.weak	SVC_Handler
	.thumb_set SVC_Handler,Default_Handler

	.weak	DebugMon_Handler
	.thumb_set DebugMon_Handler,Default_Handler

	.weak	PendSV_Handler
	.thumb_set PendSV_Handler,Default_Handler

	.weak	SysTick_Handler
	.thumb_set SysTick_Handler,Default_Handler

	.weak	SystemInit

.section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
	b	Infinite_Loop
.size	Default_Handler, .-Default_Handler

.section .text.Reset_Handler
    .weak Reset_Handler @ weak: a different definition elswhere will replace this definintion.
    .type Reset_Handler, %function

Reset_Handler:
    movs r1, #0
    b loop_copy

copy_init:
    ldr r3, =_sidata
    ldr r3, [r3, r1] @ [r] location pointed by r
    str r3, [r0, r1]
    adds r1, r1, #4

loop_copy: @ a for loop for copying initialized data
    ldr r0, =_sdata @ load address of _sdata to r0
    ldr r3, =_edata
    adds r2, r0, r1
    cmp r2, r3
    bcc copy_init
    
    b loop_clear_bss

clear_bss: @ initialize bss section with 0s
    movs r3, #0
    str r3, [r2], #4

loop_clear_bss:
    ldr r3, =_ebss
    cmp r2, r3
    bcc clear_bss

    bl system_init

    bl main
    bx lr @ return - there is nothing to return to
.size Reset_Handler, .-Reset_Handler @ size of Reset_Handler defined as size of this section

@ We can call attribute constructors from C here.