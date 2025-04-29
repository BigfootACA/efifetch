.text
.align 4
.globl _start
.type _start,%function
_start:
	subq $24, %rsp
	movq %rcx, 16(%rsp)
	movq %rdx, 8(%rsp)
	lea ImageBase(%rip), %rdi
	lea _DYNAMIC(%rip), %rsi
	call relocate
	movq 16(%rsp), %rcx
	movq 8(%rsp), %rdx
	call initialize
	movq 16(%rsp), %rcx
	movq 8(%rsp), %rdx
	call uefi_main
	addq $24, %rsp
.L_exit:
	ret
