#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


float calcAverage(int num, ...) {
    va_list list;
    int val;
    int count = 0;
    int sum = 0;

    va_start(list, num);
    val = num;
    while (val != -1) {
        count++;
        sum += val;
        val = va_arg(list,
        int);
    }

    va_end(list);
    if (count != 0)
        return ((float) sum) / count;

    return 0;
}


char *combiningStrings(const char *str, ...) {
    va_list list;
    const char *strTemp;
    char *longStr = NULL;
    int combineLength = 0;
    int len;

    va_start(list, str);
    strTemp = str;
    while (strTemp != NULL) {
        len = (int) strlen(strTemp);
        longStr = (char *) realloc(longStr, (combineLength + len + 1) * sizeof(char));
        if (!longStr)
            return NULL;

        if (combineLength == 0) {
            strcpy(longStr, strTemp);
            combineLength = len;
        } else {
            strcat(longStr, strTemp);
            combineLength += len;
        }

        strTemp = va_arg(list,
        const char*);
    }

    va_end(list);
    return longStr;
}

void manipulateArray(const void *arr, int size, void(*func)(const void *arr, int length), ...) {
    va_list list;
    void (*funcTemp)(const void *arr, int length) =NULL;

    va_start(list, func);
    funcTemp = func;
    while (funcTemp != NULL) {
        funcTemp(arr, size);
        funcTemp = va_arg(list,
        void*);
    }

    va_end(list);
}


void printArrInt(const void *arr, int size) {
    int *arrI = (int *) arr;
    for (int i = 0; i < size; i++)
        printf("%d  ", arrI[i]);
    printf("\n");
}

void printSumArrInt(const void *arr, int size) {
    int *arrI = (int *) arr;
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += arrI[i];

    printf("sum = %d\n", sum);
}

void printMaxArrInt(const void *arr, int size) {
    int *arrI = (int *) arr;
    int max = arrI[0];
    for (int i = 1; i < size; i++) {
        if (arrI[i] > max)
            max = arrI[i];
    }
    printf("max = %d\n", max);
}
