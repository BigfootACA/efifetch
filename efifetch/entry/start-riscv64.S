.text
.globl _start
.type _start,%function
_start:
	addi sp, sp, -24
	sd a0, 0(sp)
	sd a1, 8(sp)
	sd ra, 16(sp)
	lla a0, ImageBase
	lla a1, _DYNAMIC
	call relocate
	bne a0, zero, .L_exit
	ld a1, 8(sp)
	ld a0, 0(sp)
	call initialize
	ld a1, 8(sp)
	ld a0, 0(sp)
	call uefi_main
	ld ra, 16(sp)
.L_exit:
	addi sp, sp, 24
	ret
