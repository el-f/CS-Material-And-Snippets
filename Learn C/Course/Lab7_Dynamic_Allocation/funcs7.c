//
// Created by Elazar on 30/11/2020.
//

#include <malloc.h>
#include <stdio.h>
#include <mem.h>
#include <ctype.h>

int *getEvensV1(const int *arr, int size, int *evensCount) {
    *evensCount = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) (*evensCount)++;
    }

    int *evens = malloc(sizeof(int) * (*evensCount));
    if (evens == NULL) return NULL;
    for (int i = 0, j = 0; i < size; i++) {
        if (arr[i] % 2 == 0) evens[j++] = arr[i];
    }

    return evens;
}

int *getEvensV2(const int *arr, int size, int *evensCount) {
    *evensCount = 0;
    int *evens;
    evens = malloc(0);
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            evens = realloc(evens, (*evensCount + 1) * sizeof(int));
            if (evens == NULL) return NULL;
            evens[(*evensCount)++] = arr[i];
        }
    }
    return evens;
}

void printArray(const int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void initArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter int for index %d:\n", i);
        scanf(" %d", &arr[i]);
    }
}

int scanInt() {
    int num;
    scanf(" %d", &num);
    return num;
}

#define MAX_LENGTH 255

char *getStr(char *buf, size_t size) {
    if (buf != NULL && size > 0) {
        if (fgets(buf, size, stdin)) {
            buf[strcspn(buf, "\n")] = '\0'; //strcspn return index of _control char or str len if char not found
            return buf;
        }
        *buf = '\0';
    }
    return NULL;
}

char *getStrAuto() {
    char *theStr = NULL;
    int len;
    char inpStr[MAX_LENGTH]; //var to hold str that user gives
    printf("Enter A String:");
    getStr(inpStr, sizeof(inpStr));

    len = strlen(inpStr) + 1; // +1 for '\0'

    theStr = malloc(len * sizeof(char)); //allocate mem
    if (theStr != NULL) strcpy(theStr, inpStr); //fill mem

    return theStr;
}

void strToLower(char *c) {
    for (; *c; ++c) *c = tolower(*c);
}

#define BREAK "bye"

char *concatEndlessly() {
    char str[MAX_LENGTH];
    char *newStr;
    int isFirst = 1;

    printf("Enter '$' to end\n");

    while (1) {
        newStr = getStrAuto();
        strToLower(newStr);
        if (!strcmp(newStr, BREAK)) break;
        if (isFirst) {
            strcpy(str, newStr);
            isFirst = 0;
        } else {
            strcat(str, "$");
            strcat(str, newStr);
        }
    }
    free(newStr);

    char *ret = malloc((strlen(str) + 1) * sizeof(char)); //allocate mem
    if (ret != NULL) strcpy(ret, str); //fill mem

    return ret;
}

