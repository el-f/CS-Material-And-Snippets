turn_right = lambda: [turn_left(), turn_left(), turn_left()]
turn_180   = lambda: [turn_left(), turn_left()]

take()
steps = 0

def move_and_drop():
    global steps
    move()
    steps += 1
    if steps > 8 and carries_object(): put()

while not at_goal() or carries_object():
    if right_is_clear():
        turn_right()
        move_and_drop()
    else:
        turn_left();
    while not at_goal() and carries_object() and not right_is_clear() and front_is_clear():
        move_and_drop()

 
################################################################
# WARNING: Do not change this comment.
# Library Code is below.
################################################################
