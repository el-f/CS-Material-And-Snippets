#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#include "Utils.h"

#define MIN 1
#define MAX 99

void printMat(const int *mat, int rows, int cols) {
    printf("\n");
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%5d", *mat);
            mat++;
        }
        printf("\n");
    }
    printf("\n");
}

void initMat(int *mat, int rows, int cols, bool numberGame) {
    int size = rows * cols;
    for (int i = 0; i < size; i++) {
        if (numberGame) {
            *(mat + i) = (i < size - 1) ? i + 1 : 0;
        } else {
            *(mat + i) = getRandom(MIN, MAX);
        }
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int getRandom(int min, int max) {
    static bool initialized = false; // only false on first call to function
    if (!initialized) {
        srand(time(0));
        initialized = true;
    }
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

int scanInt() {
    int num;
    scanf(" %d", &num);
    return num;
}

char scanChar() {
    char chr;
    scanf(" %c", &chr);
    return toupper(chr);
}
