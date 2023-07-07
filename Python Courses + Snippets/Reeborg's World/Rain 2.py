turn_right = lambda: [turn_left(), turn_left(), turn_left()]
turn_180   = lambda: [turn_left(), turn_left()]
  
# enter room - get to the door then take a right
while not at_goal(): move()
turn_right();
while not wall_in_front(): move();
turn_left()

def handle_possible_wall():
    move()
    wr = wall_on_right()
    turn_180()
    move()
    turn_left()
    if wr:
        build_wall()
        turn_left()
    else:
        move()
        
while not at_goal():
    if right_is_clear():
        handle_possible_wall()
    elif front_is_clear():
        move();
    else: # corner
        turn_left()
################################################################
# WARNING: Do not change this comment.
# Library Code is below.
################################################################
