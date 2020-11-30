#include <stdio.h>

#include "PictureManipulation.h"
#include "Utils.h"

#define SIZE 3

int coord2Index(int row, int col, int rowSize) {
    return row * rowSize + col;
}

void rotate(int *mat, int size, bool clockwise) {
    int current, right, left, bottom, temp;

    for (int row = 0; row < size / 2; row++) {
        for (int col = row; col < size - row - 1; col++) {
            getRotationIndexes(&current, &right, &left, &bottom, row, col, size);

            temp = *(mat + current);

            if (clockwise) {
                rotateClockwise(mat, current, right, left, bottom, temp);
            } else {
                rotateCounterClockwise(mat, current, right, left, bottom, temp);
            }
        }
    }
}

// get simple array indexes for row/col coordinates of matrix
void getRotationIndexes(int *current, int *right, int *left, int *bottom, int row, int col, int size) {
    *current = coord2Index(row, col, size);
    *right = coord2Index(col, size - 1 - row, size);
    *left = coord2Index(size - 1 - col, row, size);
    *bottom = coord2Index(size - 1 - row, size - 1 - col, size);
}

void rotateClockwise(int *mat, int current, int right, int left, int bottom, int temp) {
    *(mat + current) = *(mat + left);
    *(mat + left) = *(mat + bottom);
    *(mat + bottom) = *(mat + right);
    *(mat + right) = temp;
}

void rotateCounterClockwise(int *mat, int current, int right, int left, int bottom, int temp) {
    *(mat + current) = *(mat + right);
    *(mat + right) = *(mat + bottom);
    *(mat + bottom) = *(mat + left);
    *(mat + left) = temp;
}

void flipHorizontal(int *mat, int size) {
    int row, left, right;
    for (row = 0; row < size; row++) {
        left = row * size;
        right = coord2Index(row, size - 1, size);
        while (left < right) {
            swap(mat + right, mat + left);
            left++;
            right--;
        }
    }
}

void flipVertical(int *mat, int size) {
    int col, top, bottom;
    for (col = 0; col < size; col++) {
        top = col;
        bottom = coord2Index(size - 1, col, size);
        while (top < bottom) {
            swap(mat + top, mat + bottom);
            top += size;
            bottom -= size;
        }
    }
}

void pictureManipulation() {
    bool manipulated = false;
    int mat[SIZE][SIZE];
    initMat((int *) mat, SIZE, SIZE, false);

    int choice;
    do {
        if (!manipulated) { manipulated = true; }
        else { printf("\n--------- picture after manipulation ---------\n"); }

        printMat((int *) mat, SIZE, SIZE);

        printf("Please choose one of the following options:\n");
        printf("1 - 90 degree clockwise\n");
        printf("2 - 90 degree counter-clockwise\n");
        printf("3 - Flip Horizontal (around the vertical axis)\n");
        printf("4 - Flip Vertical (around the horizontal axis)\n");
        printf("-1 - Quit\n");

        choice = scanInt();
        switch (choice) {
            case 1:
                rotate((int *) mat, SIZE, true);
                break;

            case 2:
                rotate((int *) mat, SIZE, false);
                break;

            case 3:
                flipHorizontal((int *) mat, SIZE);
                break;

            case 4:
                flipVertical((int *) mat, SIZE);
                break;

            case -1:
                break;

            default:
                printf("Invalid Input!\n");
                manipulated = false;
        }
    } while (choice != -1);
}
