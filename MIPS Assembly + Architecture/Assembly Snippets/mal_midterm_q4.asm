# Computer Architecture
# Question 4(25%)
	  	
################# Data segment #####################
.data
array:      .byte  -12,15,15,14,98,0,3,8
str:        .space 8


################# Code segment #########################

.text	
.globl main

main:		
answer:
	li      $t7,'='
	li      $t6,'1'
	li      $t5,'2'
	la      $a1, array
	li      $t0, 0
loop:	
	lb      $t1,0($a1)
	lb      $t2,1($a1)
	subu    $t1,$t1,$t2
	bnez    $t1,not_zero
	sb      $t7,str($t0)
	j       cont
not_zero:
	andi    $t1,$t1,0x1		# mask with 1
	bnez    $t1,not_even
	sb      $t5,str($t0)
	j       cont
not_even:
	sb      $t6,str($t0)
cont:	
	addi    $a1,$a1,1
	addi    $t0,$t0,1
	blt     $t0,7,loop

	li      $v0,4			# print result
	la      $a0,str
	syscall	
exit:
	li      $v0,10
	syscall



