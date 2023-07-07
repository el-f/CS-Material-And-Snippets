turn_right = lambda: [turn_left(), turn_left(), turn_left()]
a = [0] * 4 # r,u,l,d
stage = 0
finished = lambda: all(a) and a[0] == a[2] and a[1] == a[3]
while not finished():
    if right_is_clear():
        turn_right(); stage = (stage - 1) % 4
        move(); a[stage] += 1
        while object_here():
            take()
    else:
        turn_left(); stage = (stage + 1) % 4
    
    while not finished() and not right_is_clear() and front_is_clear():
        move(); a[stage] += 1
        while object_here(): take()

################################################################
# WARNING: Do not change this comment.
# Library Code is below.
################################################################
