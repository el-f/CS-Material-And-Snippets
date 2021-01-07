#include <stdio.h>
#include <ctype.h>

#include "arrays.h"

void PrintArray(const int *arr, int size) {
    for (int i = 0; i < size; i++, arr++) {
        printf("%d ", *arr);
    }
    printf("\n");
}

void InitArray(int *arr, int size) {
    for (int i = 0; i < size; i++, arr++) {
        printf("Enter int for index %d: ", i);
        scanf("%d", arr);
    }
}

void PrintMat(int *mat, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%5d", *mat);
            mat++;
        }
        printf("\n");
    }
}

void InitMat(int *mat, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("enter int for cell (%d,%d): ", i, j);
            scanf("%d", mat);
            mat++;
        }
        printf("\n");
    }
}

void PrintArrayRevers_Offset(int *arr, int size) {
    printf("reversed: ");
    for (int i = size - 1; i >= 0; i--) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

void PrintArrayRevers_WP(int *arr, int size) {
    printf("reversed: ");
    for (int *end = arr + size - 1; end >= arr; end--) {
        printf("%d ", *end);
    }
    printf("\n");
}
