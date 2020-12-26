//
// Created by Elazar on 01/12/2020.
//
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>

#include "funcs7B.h"

int scanInt() {
    int num;
    scanf(" %d", &num);
    return num;
}

int scanChar() {
    char chr;
    scanf(" %c", &chr);
    return chr;
}

int scanBool() {
    char bool;
    while (1) {
        bool = (char) toupper(scanChar());
        if (bool == 'Y' || bool == 'N') return bool == 'Y' ? 1 : 0;
        else printf("Invalid Boolean!\n");
    }
}

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
    getStr(inpStr, sizeof(inpStr));

    len = (int) strlen(inpStr) + 1; // +1 for '\0'

    theStr = malloc(len * sizeof(char)); //allocate mem
    if (theStr != NULL) strcpy(theStr, inpStr); //fill mem

    return theStr;
}