def turn_right():
    turn_left(); turn_left(); turn_left();
 
def move_n(n=1):
    for _ in range(n): move()
    
def harvest_one_row(row_len):
    while object_here(): take()
    for _ in range(row_len):
        move()
        while object_here(): take()

# get to corner of grid
move_n(2)
turn_left()
move_n(2)
turn_right()

# 3 times do one row forward and one row back
for _ in range(3):
    harvest_one_row(5)
    turn_left()
    move()
    turn_left()
    harvest_one_row(5)
    turn_right()
    move()
    turn_right()
################################################################
# WARNING: Do not change this comment.
# Library Code is below.
################################################################
