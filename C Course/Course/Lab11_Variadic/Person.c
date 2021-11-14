#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Person.h"

void printPersonArr(const void *arr, int size) {
    Person *pPerArr = (Person *) arr;
    for (int i = 0; i < size; i++) {
        printf("Person: %s id %d\n", pPerArr[i].name, pPerArr[i].id);
    }
    printf("\n");
}


void printPersonBiggestID(const void *arr, int size) {
    Person *pPerArr = (Person *) arr;
    int indexMax = 0;

    for (int i = 1; i < size; i++) {
        if (pPerArr[indexMax].id < pPerArr[i].id)
            indexMax = i;
    }
    printf("\n-------------Max Person id------------\n");
    printf("Person: %s id %d\n", pPerArr[indexMax].name, pPerArr[indexMax].id);
    printf("\n");
}

void printPersonShortestName(const void *arr, int size) {

    Person *pPerArr = (Person *) arr;
    int minlen = (int) strlen(pPerArr[0].name);
    int indexMin = 0;
    int len;

    for (int i = 1; i < size; i++) {
        len = (int) strlen(pPerArr[i].name);
        if (len < minlen) {
            minlen = len;
            indexMin = i;
        }
    }
    printf("\n-------------- Shortest Person name -----------------\n");
    printf("Person: %s id %d\n", pPerArr[indexMin].name, pPerArr[indexMin].id);
    printf("\n");
}
