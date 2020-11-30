CC = gcc
OBJ = Program.o Utils.o PictureManipulation.o NumberGame.o
EXEC = program
DEBUG = -g
C_FLAG = -std=c99 -Wall -Werror $(DEBUG)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@

NumberGame.o: NumberGame.c NumberGame.h Utils.h
PictureManipulation.o: PictureManipulation.c PictureManipulation.h Utils.h
Program.o: Program.c PictureManipulation.h NumberGame.h Utils.h
Utils.o: Utils.c Utils.h


clean:
	rm -f $(EXEC) $(OBJ)