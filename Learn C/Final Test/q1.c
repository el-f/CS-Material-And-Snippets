#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "q1.h"


void Q1() {

    char str1[] = "This is";
    char str2[] = "A good day";
    char str3[] = "abcdefghijklmnopqrstuvwxyz";
    int numOfStrings;
    int longestStrIndex;
    int mostWordsIndex;

    char **strArr = createArrOfStrings(&numOfStrings, &longestStrIndex, &mostWordsIndex, str1, str2, str3, NULL);

    printf("\n----- The Strings ------------\n");
    for (int i = 0; i < numOfStrings; i++) {
        puts(strArr[i]);
    }

    printf("\n----- The Longest String ------------\n");
    puts(strArr[longestStrIndex]);

    printf("\n----- The most words String ------------\n");
    puts(strArr[mostWordsIndex]);

    for (int i = 0; i < numOfStrings; i++) {
        free(strArr[i]);
    }
    free(strArr);
}


char **createArrOfStrings(int *numOfStrings, int *longestStrIndex, int *mostWordsIndex, const char *str, ...) {
    va_list list;
    const char *strTemp;
    char **arr = malloc(0);
    *numOfStrings = 0;
    *longestStrIndex = 0;
    *mostWordsIndex = 0;

    va_start(list, str);
    strTemp = str;
    while (strTemp != NULL) {
        if (*numOfStrings > 0) {
            if (strlen(strTemp) > strlen(*arr + *longestStrIndex)) {
                *longestStrIndex = *numOfStrings;
            }
            if (countWordsInString(strTemp) > countWordsInString(*arr + *mostWordsIndex)) {
                *mostWordsIndex = *numOfStrings;
            }
        }

        (*numOfStrings)++;
        arr = (char **) realloc(arr, (*numOfStrings) * sizeof(char *));
        if (arr == NULL) return NULL;

        arr[*numOfStrings - 1] = _strdup(strTemp);
        if (!arr[*numOfStrings - 1]) return NULL;

        strTemp = va_arg(list, const char*);
    }

    va_end(list);
    return arr;
}

int countWordsInString(const char *str) {
    int count = 1;
    for (; *str; ++str) {
        if (*str == ' ') count++;
    }
    return count;
}