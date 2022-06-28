	.data
n: .word 5
	.text
lb $a0 , n
jal fib
addi $v1, $v0, 0

exit:
li $v0, 10
syscall

fib:
addi $sp, $sp, -12
sw $s0, 8($sp)		#Push: s0 = n  for new arg: n-1 or n-2
sw $s1, 4($sp)		#s1 = return value
sw $ra, 0($sp)		#$ra= ret3

slti $t0, $a0, 2
beq $t0, $0, then	#if n>=2
add $v0, $0, $a0	#if n=1, n=0
j end

then:	#fib(n-1)+fib(n-2)
addi $s0, $a0, 0
addi $a0, $a0, -1	#fib(n-1)
jal fib

addi $s1, $v0, 0
addi $a0, $s0, -2		#fib(n-2)
jal fib

add $v0, $s1, $v0

end:
lw $ra, 0($sp)		#pop
lw $s1, 4($sp)
lw $s0, 8($sp)
addi $sp $sp 12
jr $ra
