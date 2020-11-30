#ifndef __UTILS__
#define __UTILS__

#include <stdbool.h>

void printMat(const int *mat, int cols, int rows);

void initMat(int *mat, int cols, int rows, bool numberGame);

void swap(int *a, int *b);

int getRandom(int min, int max);

int scanInt();

char scanChar();

#endif
