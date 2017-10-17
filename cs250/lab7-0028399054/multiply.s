.section	.data

.section	.text
.global		multiply
.global		func
.global		cond1
.global		cond2
.global		term

func:
	push {lr}
	
	cmp r1, $0
	bgt cond1
	blt cond2

	b term
cond1:
	add r2,r0
	sub r1, $1
	bl func
	b term
cond2:
	sub r2,r0
	add r1, $1
	bl func
	b term

term:
	pop {lr}
	bx lr

multiply:
	push {r0,r1,lr}
	mov r2, $0
	bl func
	pop {r0,r1,lr}
	mov r0, r2
	bx lr

