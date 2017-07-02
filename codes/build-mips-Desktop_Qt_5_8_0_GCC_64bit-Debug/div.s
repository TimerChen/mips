.data
title:
	.asciiz "\t\t高精度除法演示程序\n"
tip1:
	.asciiz "\n请输入被除数：\n"
tip2:
	.asciiz "请输入除数：\n"
tip3:
	.asciiz "要输出小数点后多少位：\n"
tip4:
	.asciiz "\n是否继续？（y/n）"
err:
	.asciiz "\n除数不能为0，请重新输入\n"
dot:
	.asciiz "."
sign:
	.asciiz "-"
buf:
	.space 16 #.byte   0:16

.text
main:
#输出标题
       li  $v0, 4
       la  $a0, title
       syscall

#提示输入被除数并接收输入
restart:
       li  $v0, 4
       la  $a0, tip1
       syscall

       li  $v0, 5
       syscall
       move $t0, $v0
#提示输入除数并接收输入
input_again:
       li  $v0, 4
       la  $a0, tip2
       syscall

       li  $v0, 5
       syscall
       move $t1, $v0

#检测除数是否为0,是则输出错误信息并跳转到除数输入处,否则继续执行
       bnez $t1, next
       li  $v0, 4
       la  $a0, err
       syscall
       j   input_again
#提示输入要求的小数位数并接收输入
next:
       li  $v0, 4
       la  $a0, tip3
       syscall

       li  $v0, 5
       syscall
       move $t2, $v0
#两数进行除法运算,把运算结果保存到寄存器$t8和$t9
       div $t0, $t1
       move $s0, $zero
       mflo $t8
       mfhi $t9
#检测商是否为0,是则继续执行下一步,否则跳转到输出整数结果处
       bnez $t8, int_result
#检测被除数是否为非负数,是则检查除数,否则置$s0为1,$s0用来记录负数的个数
       bgez $t0, next_check
       add $s0, $zero, 1
#检测除数是否为非负数,是则输出-号,否则$s0加1
next_check:
       bgez $t1, print_sign
       add $s0, $s0, 1
#输出-号,如果$s0值不为1,即负数个数不为奇数,则跳过此步
print_sign:
       bne  $s0, 1, int_result
       li  $v0, 4
       la  $a0, sign
       syscall
#输出整数部分结果
int_result:
       li  $v0, 1
       move $a0, $t8
       syscall
#输出小数点
       li  $v0, 4
       la  $a0, dot
       syscall

#检测余数是否不小于0,是则跳转到下一步执行,否则取反
       bgez $t9, next_num
       neg $t9, $t9
#检测除数是否不小于0,是则转入下一步,否则取反
next_num:
       bgez $t1, isloop
       neg $t1, $t1
#余数乘以10,再除以除数,得到新的商和余数
isloop:
       move $t8, $t9
       mul $t8, $t8, 10
       div $t8, $t1
       mflo $t8
       mfhi $t9
#输出新的商
       li  $v0, 1
       move $a0, $t8
       syscall

#小数位数记录减1,当其大于0时继续回到上一标号处执行,否则转入下一步
       sub $t2, $t2, 1
       bgtz $t2, isloop
#显示提示信息是否要重新开始,
       li  $v0, 4
       la  $a0, tip4
       syscall
#接收字符输入
       li  $v0, 8
       la  $a0, buf
       li  $a1, 16
       syscall
#输入的第一字符为y时则重新开始, 否则结束程序
       lb $t3, buf	#lbu
       beq $t3, 121, restart

       li  $v0, 10
       syscall
