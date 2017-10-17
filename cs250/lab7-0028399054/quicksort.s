.section	.data
debug:		.asciz "%d, %d\n"
debug2:		.asciz "Flag\n"
.section	.text
.global quicksort
.global qs
.global terminate
.global partition
.global parfor
.global endparfor
qs:
	push {r0-r2,r4-r6,r8-r9,lr}
	cmp r1,r2
	bge terminate
	bl partition
	sub r3,$4
	mov r4, r2
	mov r2, r3
	bl qs
	add r2,$8
	mov r1, r2
	mov r2, r4
	bl qs
	b terminate

terminate:
	pop {r0-r2,r4-r6,r8-r9,lr}
	bx lr
	
partition:
	push {r0-r2,r4-r6,r8-r9,lr}
	ldr r4,[r0,r2] 		@x = A[r]
	mov r5, r1		@i = p - 1
	sub r5, $4
	mov r6, r1		@j = p
	sub r2, $4		@r -= 1
	b parfor		@enter for loop
parfor:
	cmp r6, r2		@j<r-1
	bgt endparfor
	ldr r8,[r0,r6]		@get A[j] before increment
	add r6, $4

	cmp r8, r4		@if A[j] <= x
	bgt parfor

	sub r6, $4
	add r5, $4		@ i++
	ldr r3, [r0,r5]		@swap A[j] and A[i]
	ldr r9, [r0,r6]
	str r3, [r0,r6]
	str r9, [r0,r5]
	add r6, $4
	b parfor
	
endparfor:
	add r2, $4		@restore r2
	add r5, $4		@i++
	ldr r3, [r0,r5]		@swap A[i+1] and A[r]
	ldr r9, [r0,r2]
	str r3, [r0,r2]
	str r9, [r0,r5]
	mov r3, r5		@put i in return value
	pop {r0-r2,r4-r6,r8-r9,lr}
	bx lr
quicksort:
	push {r0,r1,lr}
	
	sub r1, $1
	mov r3, $4
	mul r2, r1, r3
	mov r1, $0	

	bl qs
	
	pop {r0,r1,lr}
	bx lr
	
	mov r7, $1
	svc $0
	.end
