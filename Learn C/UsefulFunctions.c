#include <mem.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

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

#define MAX_LENGTH 256

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

void strToUpper(char *c) {
    for (; *c; ++c) *c = toupper(*c);
}

char *toHexString(int num) {
    char dig2;
    int dig1;
    char *str;
    if (num == 0) {
        str = (char *) malloc(1);
        *str = '\0';
        return str;
    }
    dig1 = num % 16;
    if (dig1 <= 9)
        dig2 = '0' + dig1;
    else
        dig2 = 'A' - 10 + dig1;

    str = toHexString(num / 16);
    str = (char *) realloc(str, strlen(str) + 2);
    int len = strlen(str);
    str[len] = dig2;
    str[len + 1] = '\0';
    return str;
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

void reverseArray(int *arr, int size)
{
    int right = size - 1;
    for (int left = 0; left < right; left++, right--)
    {
        int temp = *(arr + right);
        *(arr + right) = *(arr + left);
        *(arr + left) = temp;
    }
}
