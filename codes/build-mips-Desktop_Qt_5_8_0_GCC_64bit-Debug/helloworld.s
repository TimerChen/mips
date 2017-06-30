	.data
_string:
	.asciiz "Hello World\n"

	.text
main:
	la $a0 _string
	li $v0 4
	syscall
	li $a0 0
	li $v0 17
	syscall
