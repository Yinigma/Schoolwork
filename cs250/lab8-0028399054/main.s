.section	.data
yesString:
	.asciz "yes"
formatString:
	.asciz "%s"
formatNum:
	.asciz "%d\n"
userInput:
	.space 128

.section	.text
.global main
main:
	ldr r0, =formatString
	ldr r1, =userInput
	bl scanf
	ldr r0, =userInput
	ldr r1, =yesString
	bl strcmp 
	cmp r0, #0
	beq yes
	b no

yes:
	@ This function call sets up wiringPi, just like Lab 5
	bl wiringPiSetup	@ wiringPiSetup()

	@ we need to call this next setup to use the ADC w/ SPI
	mov r0, #100
	mov r1, #0
	bl mcp3004Setup		@ mcp3004Setup(100, 0);

	bl volButt
	mov r8, r0

	mov r4, #0
	mov r5, #0
	b read
read:
	mov r0, #100
	bl analogRead
	add r5, r5, r0
	add r4, r4, #1
	cmp r4, #16
	beq decide
	b read

decide:
	mov r6, #4
	lsr r5, r6
	mov r0, #0
	cmp r5, #700
	blt play
	mov r0, #1
	cmp r5, #900
	blt play
	mov r0, #2
	b play

play:
	
	bl playSong
	mov r0, #27
	mov r1, #0
	bl softPwmWrite

	ldr r0, =formatString
	ldr r1, =userInput
	bl scanf
	ldr r0, =userInput
	ldr r1, =yesString
	bl strcmp
	mov r4, #0
	mov r5, #0
	cmp r0, #0
	beq read
	b no

	
no:
	mov r0, r8
	mov r1, #9
	bl kill
	mov r7, #1
	swi 0
	
