turn_right = lambda: [turn_left(), turn_left(), turn_left()]

while not at_goal():
    if right_is_clear():
        turn_right()
        move();
    else:
        turn_left();
    while not at_goal() and not right_is_clear() and front_is_clear():
        move()

################################################################
# WARNING: Do not change this comment.
# Library Code is below.
################################################################
