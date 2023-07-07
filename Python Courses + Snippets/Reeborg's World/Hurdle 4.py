turn_right = lambda: [turn_left(), turn_left(), turn_left()]

while not at_goal():
    while not at_goal() and front_is_clear() and wall_on_right(): move()
    if at_goal(): break
    if wall_on_right(): turn_left()
    else:
        turn_right()
        move()

################################################################
# WARNING: Do not change this comment.
# Library Code is below.
################################################################
