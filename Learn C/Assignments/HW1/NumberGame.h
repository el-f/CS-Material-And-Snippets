#ifndef __NUMBERGAME__
#define __NUMBERGAME__

int getColumn(int index, int row, int rowSize);

int isWinningBoard(const int *mat, int rows, int cols);

int isEdgeMove(int zeroPos, int newPos, int rowSize);

int isNextToEmpty(int zeroPos, int newPos, int rowSize);

int isCancelingLastMove(int lastDir, int newDir);

void chooseRandomDir(int *direction, int rowSize, int zeroPos, int *newDir);

void shuffle(int *mat, int *zeroPos, int rows, int cols, int shuffleCount);

int findNum(const int *mat, int rows, int cols, int num);

int move(int *mat, int *zeroPos, int rows, int cols, int num);

void numberGame();

#endif
