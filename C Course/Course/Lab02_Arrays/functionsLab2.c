#include "arrays.h"

int CheckArray(int arr[], int size)
{
	for (int i = 1; i < size; i++) {
		if (arr[i] < arr[i-1]) {
			return 0;
		}
	}
	return 1;
}

int CountCharInMat(char mat[][COLS], int rows, int cols, char tav)
{	
	
	if (cols > COLS) {
        cols = COLS;
    }
    
	int count = 0;
	for (int i = 0; i < rows; i++ ) {
		for (int j = 0; j < cols; j++ ) {
			if (mat[i][j] == tav) {
				count++;
			}
		}
	}
	return count;
}
