.section        .data
nf:		.asciz "%d"
nfe:		.asciz "%d\n"
strf:		.asciz "%s"
strs:		.space 100
.section        .text
.global         main
.global		term
.global		itl

main:
	mov r6, #0
	
	ldr r0, =strf
	ldr r1, =strs
	bl scanf

	ldr r4, =strs
	
	b itl


itl:
	ldr r5, [r4]
	cmp r5, #0
	beq term
	add r4, #1
	add r6, #1
	b itl

term:
	ldr r0, =nfe
	mov r1, r6
	bl printf

	mov r0, $0	
	bl fflush
	
        mov r7, $1          @exit syscall
        svc $0              @wake kernel
        .end
