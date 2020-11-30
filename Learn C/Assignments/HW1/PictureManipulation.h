#ifndef __PICTUREMANIPULATION__
#define __PICTUREMANIPULATION__

#include <stdbool.h>

int coord2Index(int row, int col, int rowSize);

void rotate(int *mat, int size, bool clockwise);

void getRotationIndexes(int *current, int *right, int *left, int *bottom, int row, int col, int size);

void rotateClockwise(int *mat, int current, int right, int left, int bottom, int temp);

void rotateCounterClockwise(int *mat, int current, int right, int left, int bottom, int temp);

void flipHorizontal(int *mat, int size);

void flipVertical(int *mat, int size);

void pictureManipulation();

#endif
