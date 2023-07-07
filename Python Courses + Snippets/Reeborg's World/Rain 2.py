turn_right = lambda: [turn_left(), turn_left(), turn_left()]
turn_180   = lambda: [turn_left(), turn_left()]
built_any = False
  
# enter room - get to the door then take a right
while not at_goal(): move()
turn_right();
while not wall_in_front(): move();
turn_left()

def is_next_wall():
    move()
    wall = wall_on_right()
    turn_180(); move(); turn_180();
    return wall
    
def move_and_check():
    move()
    if not wall_on_right() and not at_goal():
        # validate that is window
        if wall_in_front(): return # corner
        if not is_next_wall(): # window is always between two walls
            turn_right(); move();
            return
        
        turn_right()
        build_wall()
        global built_any
        built_any = True
        turn_left()
        
while not at_goal() or not built_any:
    if right_is_clear():
        turn_right()
        move_and_check();
    else:
        turn_left();
    
################################################################
# WARNING: Do not change this comment.
# Library Code is below.
################################################################
