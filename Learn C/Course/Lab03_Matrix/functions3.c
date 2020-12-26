#include <stdio.h>
#include "functions3.h"

int Calc(float x, float y, float *div, float *mult)
{
    if (y == 0)
    {
        return 0;
    }
    else
    {
        *mult = x * y;
        *div = x / y;

        return 1;
    }
}

void ChangeChar(char *c)
{
    if (0 <= *c && *c <= 9)
    {
        *c = 'D';
    }
    else if ('A' <= *c && *c <= 'Z')
    {
        *c = 'C';
    }
    else if ('a' <= *c && *c <= 'z')
    {
        *c = 'S';
    }
    else
    {
        *c = 'O';
    }
}

int ReversePositive(int *num)
{

    if (*num > 0)
    {
        int reversed = 0;
        while (*num != 0)
        {
            int digit = *num % 10;
            reversed = reversed * 10 + digit;
            *num /= 10;
        }
        *num = reversed;
        return 1;
    }
    return 0;
}

void SumAndCountEvensInArray(int arr[], int size, int *sum, int *evens)
{
    int temp;
    for (int i = 0; i < size; i++)
    {
        temp = arr[i];
        if (temp % 2 == 0)
        {
            *evens += 1;
        }
        *sum += arr[i];
    }
}

void CountDivAndDigSumInArray(int arr[], int size, int n, int *nSumsNum, int *nDivsNum)
{
    int temp;
    for (int i = 0; i < size; i++)
    {
        temp = arr[i];
        if (temp % n == 0)
        {
            *nDivsNum += 1;
        }
        if (SumDig(temp) == n)
        {
            *nSumsNum += 1;
        }
    }
}

int SumDig(int num)
{
    int res = 0;
    while (num != 0)
    {
        res += num % 10;
        num /= 10;
    }
    return res;
}