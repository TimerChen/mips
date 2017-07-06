	.text
calc:
	add $t2 $t0 $t1
	#go back
	jr $31

main:
	#read a
	li $v0 5
	syscall
	move $t0 $v0

	#read b
	li $v0 5
	syscall
	move $t1 $v0

	#use calc
	add $t2 $t0 $t1
	#jal calc

	#output a+b
	move $a0 $t2 #move
	li $v0 1
	syscall

	#return 0
	li $a0 0
	li $v0 17
	syscall
