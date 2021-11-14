CC = gcc
OBJ = arrays.o functions3.o exe.o Prog3.o
EXEC = program
DEBUG = -g
C_FLAG = -std=c99 -Wall -Werror $(DEBUG)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@

arrays.o: arrays.c
exe.o: exe.c exe.h functions3.h
functions3.o: functions3.c functions3.h
Prog3.o: Prog3.c exe.h

clean:
	rm $(EXEC) $(OBJ)