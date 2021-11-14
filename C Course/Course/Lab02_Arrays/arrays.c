#include <stdio.h>
#include <ctype.h>
#include "arrays.h"

void PrintArray(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
}

void InitArray(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		printf("enter int for index %d: ", i);
		scanf("%d", &arr[i]);
	}
}

void PrintMat(char mat[][COLS], int rows, int cols) {
	
	if (cols > COLS) {
        cols = COLS;
    }
	
	for (int i = 0; i < rows; i++ ) {
		for (int j = 0; j < cols; j++ ) {
			printf("%c ", mat[i][j]);
		}
		printf("\n");
	}
}

void InitMat(char mat[][COLS], int rows, int cols) {
	if (cols > COLS) {
		cols = COLS;
	}
	for (int i = 0; i < rows; i++ ) {
		for (int j = 0; j < cols; j++ ) {
			printf("enter char for cell (%d,%d): ", i, j);
			do {
				scanf("%c", &mat[i][j]);
			} while (isspace(mat[i][j]));
		}
	}
	printf("\n");
}
