//
// Created by Elazar on 30/11/2020.
//

#include <stdio.h>
#include <malloc.h>
#include "funcs7.h"

void Q1() {
    printf("How Many Numbers?");
    int size = scanInt();
    int *arr = malloc(size * sizeof(int));
    initArray(arr, size);
    printArray(arr, size);

    int evensSize;
    int *evens = getEvensV1(arr, size, &evensSize);
    if (evens == NULL) return;
    if (evensSize > 0) {
        printf("evenSize = %d\n", evensSize);
        printf("evens array:\n");
        printArray(evens, evensSize);
    } else printf("No Evens!\n");

    evens = getEvensV2(arr, size, &evensSize);
    if (evens == NULL) return;
    if (evensSize > 0) {
        printf("evenSize = %d\n", evensSize);
        printf("evens array:\n");
        printArray(evens, evensSize);
    } else printf("No Evens!\n");

    free(arr);
}

void Q2() {
    getchar(); //clear buffer
    char *str = getStrAuto();
    if (str == NULL) return;
    printf("%s\n", str);
}

void Q3() {
    printf("%s\n", concatEndlessly());
}

int main() {
    Q1();
    Q2();
    Q3();
}