#include <stdio.h>
#include <stdlib.h>

#include "NumberGame.h"
#include "Utils.h"

#define ROWS 4
#define COLS 4

#define SHUFFLE_COUNT 9

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


int getColumn(int index, int row, int rowSize) {
    return index - row * rowSize;
}

int isWinningBoard(const int *mat, int rows, int cols) {
    int size = rows * cols;
    for (int i = 0; i < size - 2; i++) {
        if (*(mat + i) > *(mat + i + 1)) {
            return 0;
        }
    }
    return *(mat + size - 1) == 0;
}

int isEdgeMove(int zeroPos, int newPos, int rowSize) {
    int zeroX = getColumn(zeroPos, zeroPos / rowSize, rowSize);
    int newPosX = getColumn(newPos, newPos / rowSize, rowSize);

    return abs(zeroX - newPosX) + 1 == rowSize;
}

int isNextToEmpty(int zeroPos, int newPos, int rowSize) {
    return newPos == zeroPos + 1 ||
           newPos == zeroPos - 1 ||
           newPos == zeroPos + rowSize ||
           newPos == zeroPos - rowSize;
}

// For a more meaningful shuffle
int isCancelingLastMove(int lastDir, int newDir) {
    return lastDir == UP && newDir == DOWN ||
           lastDir == DOWN && newDir == UP ||
           lastDir == LEFT && newDir == RIGHT ||
           lastDir == RIGHT && newDir == LEFT;
}

void chooseRandomDir(int *direction, int rowSize, int zeroPos, int *newDir) {
    *newDir = getRandom(UP, RIGHT);
    switch (*newDir) {
        case UP:
            *direction = zeroPos - rowSize;
            break;

        case DOWN:
            *direction = zeroPos + rowSize;
            break;

        case LEFT:
            *direction = zeroPos - 1;
            break;

        case RIGHT:
            *direction = zeroPos + 1;
            break;
    }
}

void shuffle(int *mat, int *zeroPos, int rows, int cols, int shuffleCount) {
    int newPos, lastDir, newDir;
    for (int i = 0; i < shuffleCount; i++) {
        do {
            chooseRandomDir(&newPos, cols, *zeroPos, &newDir);

            if (isEdgeMove(*zeroPos, newPos, cols) || isCancelingLastMove(lastDir, newDir)) {
                newPos = -1;
            }
        } while (rows * cols <= newPos || newPos < 0);

        swap(mat + *zeroPos, mat + newPos);
        *zeroPos = newPos;
        lastDir = newDir;
    }
}

int findNum(const int *mat, int rows, int cols, int num) {
    for (int i = 0; i < rows * cols; i++) {
        if (*(mat + i) == num) {
            return i;
        }
    }
    return -1;
}

int move(int *mat, int *zeroPos, int rows, int cols, int num) {
    if (num == 0) return 0;

    int newPos = findNum((int *) mat, rows, cols, num);
    bool invalidMove = {
            newPos == -1 ||
            !isNextToEmpty(*zeroPos, newPos, cols) ||
            isEdgeMove(*zeroPos, newPos, cols)
    };
    if (invalidMove) return 0;

    swap(mat + *zeroPos, mat + newPos);
    *zeroPos = newPos;
    return 1;
}

void numberGame() {
    bool changed = true;
    int zeroPosition = ROWS * COLS - 1;
    int step;
    int mat[ROWS][COLS];
    initMat((int *) mat, ROWS, COLS, true);
    shuffle((int *) mat, &zeroPosition, ROWS, COLS, SHUFFLE_COUNT);

    while (!isWinningBoard((int *) mat, ROWS, COLS)) {
        if (changed) {
            printMat((int *) mat, ROWS, COLS);
        } else {
            printf("Invalid Step!\n");
        }

        printf("Your Step:");
        step = scanInt();
        changed = move((int *) mat, &zeroPosition, ROWS, COLS, step);
    }

    printMat((int *) mat, ROWS, COLS);
    printf("You win! The game is over!\n\n");
}
