
#include <stdio.h>
#include <ctype.h>

#include "arrays.h"
#include "functions4.h"
#include "exe.h"

#define SIZE 5

void Q_ReverseArr()
{
    int arr[5];
    int size = sizeof(arr) / sizeof(int);

    InitArray(arr, size);
    printf("Array:\n");
    PrintArray(arr, size);

    printf("Array after reverse:\n");
    ReverseArray(arr, size);
    PrintArray(arr, size);
}

#define R 5
#define C 3

void Q_PrintMat()
{
    // int mat[R][C] = {{1, 2, 3}, {4, 5, 6}};
    int mat[R][C];
    InitMat((int *)mat, R, C);
    printf("Matrix:\n");
    PrintMat((int *)mat, R, C);
}

void Q_PrintArrReverse()
{
    int arr[5] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(int);
    printf("array: ");
    PrintArray(arr, size);
    PrintArrayRevers_Offset(arr, size);
    PrintArrayRevers_WP(arr, size);
}

void Q_PrintMixMatrix()
{
    int mat[R][C];
    InitMat((int *)mat, R, C);
    printf("Matrix:\n");
    PrintMat((int *)mat, R, C);

    int half = R * C / 2;
    PrintArrayRevers_Offset((int *)mat, half);
    PrintArrayRevers_Offset((int *)mat + half, half);
}

void Q_Palindrome()
{
    int arr[5];
    int size = sizeof(arr) / sizeof(int);

    InitArray(arr, size);
    printf("\nArray: ");
    PrintArray(arr, size);

    if (CheckPalindromeArr(arr, size))
    {
        printf("Is Palindrome!\n");
    }
    else
    {
        printf("Is not Palindrome!\n");
    }
}
