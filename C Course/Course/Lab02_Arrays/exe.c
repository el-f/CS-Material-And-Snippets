#include <stdio.h>
#include <ctype.h>
#include "functionsLab2.h"

void Q1_A()
{
    // int size = 5;
    int arr[5] = {5, 3, 2, 8, 10};

    PrintArray(arr, sizeof(arr) / sizeof(int));
    if (CheckArray(arr, sizeof(arr) / sizeof(int) == 1)) {
        printf("Is a sequal\n");
    } else {
        printf("Not a sequal\n");
    }

}

void Q1_B()
{
    int arr[6];
    InitArray(arr, sizeof(arr) / sizeof(int));
    PrintArray(arr, sizeof(arr) / sizeof(int));

    if (CheckArray(arr, sizeof(arr) / sizeof(int)) == 1) {
        printf("Is a sequal\n");
    } else {
        printf("Not a sequal\n");
    }
}

void Q2()
{
    char mat[3][COLS];
    int rows = sizeof(mat) / sizeof(mat[0]);
    char ch;

    printf("Enter a char to search in matrix: ");
    do {
        scanf("%c", &ch);
    } while(isspace((unsigned char)ch));

    InitMat(mat, rows, 5);
    PrintMat(mat, rows, 5);
    printf("The char '%c' appeared %d times in the matrix\n", 
                ch, CountCharInMat(mat, rows, 5, ch));

}
