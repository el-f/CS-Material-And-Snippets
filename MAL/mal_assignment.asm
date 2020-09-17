# Title: Exercise 4
# Author: Elazar Fine
################# Data segment #####################
.data
String: .space 33 #extra one for null
msg1:	.asciiz "\n Please enter a string (max 32 chars):\n "
msg2:	.asciiz "\n The max sequence of abc in the string is:\n "
msg3:	.asciiz "\n Please enter a char to look for in the string:\n "
msg4:	.asciiz "\n The number of occurrences of the char in the string is:\n "
msg5:	.asciiz "\n Please enter X (1-9)\n "
msg6:	.asciiz "\n The string after reduction in reverse is:\n "

################# Code segment #####################
.text
.globl main
main:		# main program entry
#############
##### A #####
li $v0,4
la $a0,msg1
syscall
		
li $v0,8        #syscall type = 8
la $a0,String   #address to write to
li $a1,33     	#32 bytes + extra one for null
syscall			#read string from user

jal count_abc
move $t0,$v0

li $v0,4
la $a0,msg2
syscall

move $a0,$t0
li $v0, 1
syscall

#############
##### B #####
li $v0,4
la $a0,msg3
syscall


li $v0,12
syscall
move $a1,$v0	#argument convention
la $a0,String	
jal count_char
move $v0,$t0
li $v0,4
la $a0,msg4
syscall
move $a0,$t0
li $v0,1
syscall

#############
##### C #####
get_x:
li $v0,4
la $a0, msg5
syscall
li $v0,5
syscall
bgt $v0,9,get_x
blt $v0,1,get_x
move $a1,$v0		#argument convention
la $a0,String		#argument convention
jal delete

#############
##### D #####
li $v0,4
la $a0,msg6
syscall

la $a0,String
jal reverse

#############
li $v0, 10	# Exit program
syscall
#############

#######################
##### count_abc #######
#######################
#$a0 - String adress, $v0 - return int value
count_abc: 
li $t1,0 					#current max = 0
li $t2,0 					#overall max = 0
lb $t3,0($a0)

count_abc_loop:
lb $t4,1($a0)
bgt $t3,'z',cont_abc_loop			#\ check lower case
blt $t3,'a',cont_abc_loop			#/

bnez $t2,not_single_char_case			#\
addi $t1,$t1,1					# for case of string of size one e.g.: "a"	
move $t2,$t1					#/

not_single_char_case:
addi $t3,$t3,1					#a[i]++
bne $t3,$t4,chain_break				#compare a[i]+1 to a[i+1]
addi $t1,$t1,1					#current max ++
ble $t1,$t2,cont_abc_loop			#if (currentMax>max) {
move $t2,$t1					#max = currentMax; }
j cont_abc_loop

chain_break:			
li $t1,1 					#there is lower case but chain broke

cont_abc_loop:
addi $a0,$a0,1
lb $t3,0($a0)
bne $t3,'\n',count_abc_loop			#check if string terminated

move $v0,$t2					#loop end, return overall max
jr $ra

#######################
##### count_char ######
#######################
#$a0 - String adress, $v0 - return int value
count_char:
li $t0,0	#result
lb $t2,0($a0)

count_char_loop:
bne $a1,$t2,not_char
addi $t0,$t0,1
not_char:
addi $a0,$a0,1
lb $t2,0($a0)
bne $t2,'\n',count_char_loop

move $v0,$t0	#return result
jr $ra

#######################
##### 	delete	 ######
#######################
#$a0 - String adress, $a1 - X
delete:
li $t9,'\n'		#new line
li $t3,0		#true/false flag for first shift
add $a0,$a0,$a1		#set starting index to X
del_loop:		#/ each delete calls shift_chars loop
la $t1,0($a0)		#inner counter starts at current outer counter
shift_chars:		#inner loop to shift all chars 1 'cell' left
lb $t2,1($t1)		#get a[j+1]
beq $t2,0,end_shift	#terminate loop on null
sb $t2,0($t1)		#a[j] = a[j+1]
sb $t9,1($t1)		#make cell string end (new line)
addi $t1,$t1,1		#inner loop counter
j shift_chars		#loop terminator is beq $t2,'\n',end_shift
end_shift:
beq $t3,1,adv_del	#change $a1 only once
addi $a1,$a1,-1		#all cells shifted -1, so 'jump' value needs shift -1 as well
li $t3,1		#changed $a1 = true

adv_del:
add $a0,$a0,$a1	#index+=X
lb $t4,0($a0)
bne $t4,'\n',del_loop	#terminate loop on new line

jr $ra

#######################
##### 	reverse	 ######
#######################
#$a0 - String address
reverse:
li $t1,32 			#loop counter
la $t0,32($a0)			#copy string address
li $v0,11			
reverse_loop:
lb $a0,0($t0)
beq $a0,'\n',end_reverse_loop	#dont print
syscall
end_reverse_loop:
addi $t0,$t0,-1			#address--
addi $t1,$t1,-1			#counter--
bgez $t1,reverse_loop

jr $ra
