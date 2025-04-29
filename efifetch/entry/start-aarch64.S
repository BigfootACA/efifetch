.text
.align 12
.globl _start
.type _start,%function

_start:
	stp x29, x30, [sp, #-32]!
	mov x29, sp
	stp x0, x1, [sp, #16]
	adr x0, ImageBase
	adrp x1, _DYNAMIC
	add x1, x1, #:lo12:_DYNAMIC
	bl relocate
	cbnz x0, .L_exit
	ldp x0, x1, [sp, #16]
	bl initialize
	ldp x0, x1, [sp, #16]
	bl uefi_main
.L_exit:
	ldp x29, x30, [sp], #32
	ret
