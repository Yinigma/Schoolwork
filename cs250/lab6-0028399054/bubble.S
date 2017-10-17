.section        .data
df:		.asciz "%d"
.section        .text
.global         bubble
.global		for
bubble:
	mov r3, $4
	sub r0, $1
	mul r0, r3
	mov r3, r0
	mov r4, $0	@counter
	mov r5, $1	@sorted boolean
	b for
	

for:
	cmp r4, r3
	beq check
	mov r6, r1
	add r6, r4
	ldr r8, [r6]
	ldr r9, [r6, +$4]
	add r4, $4
	b if

if:
	cmp r8, r9
	bgt swap
	b for

swap:
	str r9, [r6]
	str r8, [r6, +$4]
	mov r5, $0
	b for

check:
	cmp r5, $1
	beq term
	mov r5, $1
	mov r4, $0
	b for

term:
	bx lr