# Computer Architecture 
# Question 3(25%)
# Input: array of 8 integer (word) sign number 
# Output: 1)save to array1 the opposite number 	(neg-->pos pos-->neg) 
# if the number divide by 4 than save the opposite divide by 4 number
# print (from left to right) the even posotive numbers of array1
################# Data segment #####################
.data
array:  .word -4,300,-600,-750,1270,-200,800,900
array1: .word 0:8  #8 word for save
msg1:   .asciiz "\n The positive even numbers of array1:\n "

################# Code segment #####################
.text
.globl main

main:							# main program entry

	li      $v0,4				# print message
	la      $a0,msg1
	syscall	
	
	li      $t0,8				# loop counter
	la      $a1,array
	la      $a2,array1

loop:	
	li      $v0,1
	lw      $a0,0($a1)
	subu    $a0,$0,$a0			# negate $a0
	move    $t2,$a0
	andi    $t2,0x3				# check if divisible by 4 using mask of 0b11=0x3
	bnez    $t2,dont_div_by_four
	sra     $a0,$a0,2			# divide by 4

dont_div_by_four:	
	sw      $a0,0($a2)			# save final result into array1
	ble     $a0,$0,cont			# check if to print
	move    $t2,$a0
	andi    $t2,0x1				# check if divisible by 2 using mask of 0b1=0x1
	bnez    $t2,cont
	syscall						# print the number (still in $a0)
	li      $v0,11
	la      $a0,32
	syscall						# print space

cont:
	addi    $a1,$a1,4
	addi    $a2,$a2,4
	addi    $t0,$t0,-1
	bgt     $t0,$0,loop
	
###################################################   
	
# end of program
exit:	
	li      $v0,10
	syscall
	


