#include "functions4.h"

void ReverseArray(int *arr, int size) {
    int right = size - 1;
    for (int left = 0; left < right; left++, right--) {
        int temp = *(arr + right);
        *(arr + right) = *(arr + left);
        *(arr + left) = temp;
    }
}

int CheckPalindromeArr(int *arr, int size) {
    int right = size - 1;
    for (int left = 0; left < right; left++, right--) {
        if (*(arr + left) != *(arr + right)) {
            return 0;
        }
    }
    return 1;
}