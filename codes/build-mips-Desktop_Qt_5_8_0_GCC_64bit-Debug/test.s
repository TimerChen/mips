	.data
	.word 1
_static_3:
	.asciiz "\""
	.align 2
	.word 0

	.data
_buffer:
	.word 0

	.text
_buffer_init:
	li $a0, 256
	li $v0, 9
	syscall
	sw $v0, _buffer
	jr $ra

	.text
main:
	jal _buffer_init
	add $fp, $zero, $sp
	li $8, 4
	add $9, $8, 1
	mul $10, $9, 4
	li $v0, 9
	move $a0, $10
	syscall
