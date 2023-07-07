while not at_goal():
    while object_here():
        take(); move();
    while carries_object(): put()
    move()    

################################################################
# WARNING: Do not change this comment.
# Library Code is below.
################################################################
