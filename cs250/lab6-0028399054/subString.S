.section        .data
sf:		.asciz "%s\n"
cf:		.asciz "%d ?= %d\n"
F1:		.asciz "F1"
F2:		.asciz "F2"
F3:		.asciz "F3"
F4:		.asciz "F4"
null:		.space 100
.section        .text
.global         subString
.global		term
.global		screen
.global		ini
.global		compare
.global		loadNull
subString:
	
	mov r5, $0
	mov r6, r0
	mov r8, r1


	mov r0, $0
	b screen

screen:

	ldrb r0, [r6]
	ldrb r1, [r8]
	cmp r0, r1
	beq ini
	cmp r0, $0
	beq loadNull
	add r6, $1
	b screen

ini:

	mov r9, r6
	mov r10, r8
	b compare

compare:

	add r9, $1
	add r10, $1

	ldrb r4, [r9]
	ldrb r5, [r10]
	
	cmp r5, #0	@success
	beq term

	cmp r4, #0	@end of source
	beq loadNull
	
	cmp r4, r5	@String and substring are still the same
	beq compare

	add r6, $1	@String and ss are not equal
			@advances pointer to avoid inf loop
	b screen	@return to screen function

loadNull:

	mov r6, $0
	b term

term:
	
	mov r0, r6
	
	bx lr
