.text
.align 4
.globl _start
.type _start,%function
_start:
	pushl %ebp
	movl %esp,%ebp
	pushl %esi
	pushl %edi
	movl 8(%ebp),%esi
	movl 12(%ebp),%edi
	call 0f
0:	popl %eax
	movl %eax,%ebx
	addl $ImageBase-0b,%eax
	addl $_DYNAMIC-0b,%ebx
	pushl %ebx
	pushl %eax
	call relocate
	addl $8,%esp
	testl %eax,%eax
	jne .L_exit
	pushl %edi
	pushl %esi
	call initialize
	addl $8,%esp
	pushl %edi
	pushl %esi
	call uefi_main
	addl $8,%esp
.L_exit:
	popl %edi
	popl %esi
	leave
	ret
