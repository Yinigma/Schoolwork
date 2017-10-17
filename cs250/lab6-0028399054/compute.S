.section        .data
n1p:		.asciz "Enter the first number:"
opp:		.asciz "Enter the operator:"
n2p:		.asciz "Enter the second number:"
out:		.asciz "Returned answer:%d\n"
inv:		.asciz "Invalid input\n"
df:		.asciz "%d"
rf:		.asciz "r1:%d, r2:%d\n"
sf:		.asciz "%s"
num1:		.word 0
op:		.space 8
num2:		.word 0
.section        .text
.global         main
.global		plus
.global		minus
.global		aster
.global		slash
.global		invalid
.global		term
.global		flipn
.global		flipd
.global		flipfin
.global		divloop
main:
	
	ldr r0, =n1p	@scan in n1
	bl printf

	ldr r0, =df
	ldr r1, =num1
	bl scanf

	ldr r0, =opp	@scan in op
	bl printf

	ldr r0, =sf
	ldr r1, =op
	bl scanf

	ldr r0, =n2p	@scan in n2
	bl printf

	ldr r0, =df
	ldr r1, =num2
	bl scanf
	
	ldr r6, =op	@move head of string to r6
	ldrb r6, [r6]
	
	ldr r4, =num1
	ldr r5, =num2
	ldr r4, [r4]
	ldr r5, [r5]
	mov r2, $0

	cmp r6,$43
	beq plus
	cmp r6,$45
	beq minus
	cmp r6,$42
	beq aster
	cmp r6,$47
	beq slash
	b invalid

plus:
	
	add r4, r5
	mov r1, r4
	b res

minus:

	sub r4, r5
	mov r1, r4
	b res
aster:

	mul r4, r5
	mov r1, r4
	b res
slash:
	mov r1, $0	
	
	cmp r4, $0
	blt flipn

	cmp r5, $0
	blt flipd
	beq invalid
	
	b divloop

flipn:
	mov r8, $-1
	mul r4, r8
	add r2, $1
	b slash

flipd:
	mov r8, $-1
	mul r5, r8
	add r2, $1
	b slash

divloop:
	cmp r4, r5
	sub r4, r5
	blt res
	add r1, $1
	beq res
	bgt divloop

flipfin:
	mov r8, $-1
	mul r1, r8
	mov r2, $0
	b res
	

invalid:
	ldr r0, =inv
	bl printf

	mov r0, $0
	bl fflush
	b term

res:
	
	cmp r2, $1
	beq flipfin
	
	ldr r0, =out
	bl printf

	mov r0, $0
	bl fflush
	b term

term:
        mov r7, $1          @exit syscall
        svc $0              @wake kernel
        .end
