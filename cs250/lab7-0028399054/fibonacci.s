.section        .data
df:		.asciz "%d\n"
.section        .text
.global         fibonacci
.global		fib
.global		morethan
.global		term

fib:
	push {r0,lr}
	cmp r0,$1
	bgt morethan
	add r1, r1, r0
	b term
morethan:
	sub r0,r0,$1
	bl fib
	sub r0, r0, $1
	bl fib
	b term
term:
	pop {r0,lr}
	bx lr

fibonacci:
	push {r0,lr}
	bl fib
	pop {r0,lr}
	mov r0, r1
	bx lr
	mov r7, $1
	svc $0
	.end
