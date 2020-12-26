CC = gcc
OBJS = arrays.c exe.c functionsLab2.c prog.c
EXEC = prog
DEBUG = -g
CFLAGS = -std=c99 -Wall -Werror $(DEBUG)


$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@


arrays.o: arrays.c arrays.h
exe.o: exe.c arrays.h functionsLab2.h
functionsLab2.o: functionsLab2.c arrays.h
prog.o: prog.c exe.h


clean:
	rm -f *.o $(EXEC)
	