	.data
n: .word 5
	.text
lb $a0 , n
jal sum
add $v1 $v1 $v0

exit:
li $v0, 10
syscall

sum:
addi $sp, $sp, -8	
sw $ra, 4($sp)					
sw $a0, 0($sp)			# push n,$ra -> stack
addi $a0, $a0, -1		# n-1 ->a0
beq $a0, $0, then		
jal sum  
then:
lw $t1, 0($sp)
lw $t2, 4($sp)			#pop $ra,n ->$t1,$t2
add $v0, $t1, $v0		# ret=n+sum(n-1)
addi $sp, $sp, 8		#stack cover
jr $ra				#return 
