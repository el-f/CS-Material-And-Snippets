def turn_right():
    turn_left(); turn_left(); turn_left();
 
def move_n(n=1):
    for _ in range(n): move()

def leave_one():
    while object_here(): take()
    put()
    
def one_row(row_len):
    leave_one()
    for _ in range(row_len):
        move()
        leave_one()

# get to corner of grid
move_n(2)
turn_left()
move_n(2)
turn_right()

# 3 times do one row forward and one row back
for _ in range(3):
    one_row(5)
    turn_left()
    move()
    turn_left()
    one_row(5)
    turn_right()
    move()
    turn_right()
################################################################
# WARNING: Do not change this comment.
# Library Code is below.
################################################################
