turn_right   = lambda: [turn_left(), turn_left(), turn_left()]
turn_180     = lambda: [turn_left(), turn_left()]

def wall_on_left():
    turn_left()
    wall = wall_in_front()
    turn_right()
    return wall

def clean_spot():
    while object_here(): take()

def go_around():
    turn_right()
    if wall_in_front():
        turn_left()
        return False
    
    move()
    turn_left()
    if wall_in_front():
        turn_left()
        move()
        turn_right()
        if wall_in_front() and wall_on_right():
            turn_180()
        return False
   
    
    move()
    if wall_in_front():
        turn_180()
        clean_spot()
        move()
        turn_right(); turn_right()
        return False
    move()
    turn_left()
    move()
    turn_right()
    return True
    

def clean_row(backtrack=True):
    while front_is_clear() or go_around():
        clean_spot()
        move()
    clean_spot()
    
    if backtrack:
        turn_180();
        while front_is_clear()  or go_around():
            clean_spot()
            move()
            
# BRUTE FORCE APPROACH

reached_corner=False
move()
clean_row(False)
turn_left()
move()
turn_left()
while not reached_corner:
    clean_row()
    turn_left()
    if wall_in_front():
        global reached_corner
        reached_corner = True
        turn_180()
        break
    move()
    turn_left()
    if reached_corner: clean_row()

while front_is_clear(): move()
turn_right()
while front_is_clear(): move()
turn_right()
while carries_object(): toss()


################################################################
# WARNING: Do not change this comment.
# Library Code is below.
################################################################
