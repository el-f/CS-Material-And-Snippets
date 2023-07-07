turn_right = lambda: [turn_left(), turn_left(), turn_left()]
turn_180   = lambda: [turn_left(), turn_left()]
a = [0] * 4 # r,u,l,d
stage = 0
horiz, vert = True, True
finished_horz = lambda: all(a[::2]) and a[0] // 2 <= a[2]
finished_vert = lambda: all(a[1::2]) and a[1] // 2 <= a[3]
finished = lambda: (not horiz or finished_horz()) and (not vert or finished_vert())

def check_horiz():
    global horiz
    if not wall_in_front(): return
    turn_180()
    if wall_in_front():     horiz = False
    turn_180()
check_horiz();

def check_vert():
    global vert
    if not wall_on_right(): return
    turn_left()
    if wall_in_front():     vert = False
    turn_right()
check_vert()

def change_stage():
    global stage
    turn_left()
    if stage == 0:
        stage = 2
        turn_left()
    elif stage == 2:
        stage = 1
        turn_180()
        vert = False
    elif stage == 1:
        stage = 3
        turn_left()
    elif stage == 3:
        stage = 0
        vert = False

while not finished():
    if horiz and finished_horz():
        horiz = False
        change_stage()
    if front_is_clear():
        move(); a[stage] += 1
    else:
        change_stage()
put()
################################################################
# WARNING: Do not change this comment.
# Library Code is below.
################################################################
