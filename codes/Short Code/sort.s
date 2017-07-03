.data
sortarry:
.word 15,23,14,25,60,10,9,11,-60,40
seprate:
.asciiz ","

.text
main:
	add $t5,$zero,10    # size of arry
	add $t4,$zero,9     #intialize first loop counter i=10
	loop1: #{
		la   $t1,sortarry    #load base address of arry,t1 as the offset address of the count
		add $t6,$zero,0     #intialize second loop counter j=0

		loop2: #{
			lw   $t0,0($t1)      #initialize t0=arry[j] as the temp value
			lw   $t7,4($t1)      # t7=arry[j+1]
			sub  $t2,$t7,$t0     #t2=arry(j+1)-temp
			bgtz  $t2,skip2      # if arry(j+1)>temp,goto skip2
			sw   $t7,0($t1)     #  arry[j]=arry[j+1]
			sw   $t0,4($t1)    #   arry[j+1]=temp

		skip2:
			add $t6,$t6,1        #j=j+1
			add $t1,$t1,4
			sub  $t2,$t4,$t6      #t2=i-j
			bgtz  $t2,loop2    #if(i>j) back to loop2
		#}

		addiu $t4,$t4,-1        #i=i-1
		lw    $a0,0($t1)
		li    $v0,1             #out put segment
		syscall
		la    $a0,seprate
		li    $v0,4
		syscall
		bne  $t4,$zero,loop1
	#}
	la   $t1,sortarry        #loop1 over,output the last number
	lw    $a0,0($t1)
	li    $v0,1
	syscall

	li   $v0,10
	syscall
