CC = gcc
OBJ = arrays.o functions4.o exe.o Prog4.o
EXEC = program
DEBUG = -g
C_FLAG = -std=c99 -Wall -Werror $(DEBUG)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@

arrays.o: arrays.c arrays.h
exe.o: exe.c arrays.h functions4.h exe.h
functions4.o: functions4.c functions4.h
Prog4.o: Prog4.c exe.h

clean:
	rm -f $(EXEC) $(OBJ)