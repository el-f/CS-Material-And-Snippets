CC = gcc
OBJS = functionsLab1.o main.o
EXEC = prog
DEBUG = -g
CFLAGS = -std=c99 -Wall -Werror $(DEBUG)


$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@

functionsLab1.o: functionsLab1.c functionsLab1.h
main.o: main.c functionsLab1.h


clean:
	rm -f *.o $(EXEC)
