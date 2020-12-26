#include <stdio.h>
#include <ctype.h>

#include "exe.h"
#include "functions3.h"
#include "arrays.h"

void Q_DivMult()
{
    float x;
    float y;
    float div = 0;
    float mult = 0;

    printf("Please Enter Two Numbers To Div And Mult: ");
    do
    {
        scanf("%f", &x);
    } while (isspace(x));
    do
    {
        scanf("%f", &y);
    } while (isspace(y));

    if (Calc(x, y, &div, &mult) != 0)
    {
        printf("%f * %f = %f\n", x, y, mult);
        printf("%f / %f = %f\n", x, y, div);
    }
    else
        printf("Cannot Divide By 0!\n");
}

void Q_Char()
{
    char ch = 'A';
    printf("Before - %c\n", ch);
    ChangeChar(&ch);
    printf("After - %c\n", ch);
}

void Q_Reverse()
{
    int num = 123456;
    printf("Before - %d\n", num);
    ReversePositive(&num);
    printf("After - %d\n", num);
}

void Q_Arr_Sum_Evens()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int sum = 0;
    int evens = 0;
    int size = sizeof(arr) / sizeof(arr[0]);
    PrintArray(arr, size);
    SumAndCountEvensInArray(arr, size, &sum, &evens);
    printf("num of evens: %d\n", evens);
    printf("sum: %d\n", sum);
}

void Q_Arr_Div_SumDig()
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 111, 21};
    int size = sizeof(arr) / sizeof(arr[0]);
    int nSumsNum = 0;
    int nDivsNum = 0;
    int n = 3;
    PrintArray(arr, size);
    CountDivAndDigSumInArray(arr, size, n, &nSumsNum, &nDivsNum);

    printf("num of numbers that sum to %d: %d\n", n, nSumsNum);
    printf("num of numbers that are divided by %d: %d\n", n, nDivsNum);
}
