.section .data
a:
	.zero	8
b:
	.zero	80
.section .text
.global main
main:
bb1:
	sub	sp, sp, #32
	mov	x2, #1
	str	x2, [sp, #20]
	mov	x2, #223
	str	x2, [sp, #24]
	ldr	x9, [sp]
	str	x9, [sp, #16]
	adr	x3, a
	add	x3, x3, #4
	mov	x9, x3
	mov	x2, #1
	str	x2, [x9]
	ldr	x9, [sp]
	adr	x3, b
	add	x3, x3, #8
	mov	x10, x3
	add	x11, x10, #4
	str	x9, [x11]
	mov	x0, #0
	add	sp, sp, #32
	ret
