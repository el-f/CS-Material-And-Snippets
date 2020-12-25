#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

int scanInt() {
    int num;
    scanf(" %d", &num);
    return num;
}

#define STR_MAX_LENGTH 256

int isAllDigits(char *string) {
    int i;
    for (i = 0; i < strlen(string) - 1; i++) {
        if (!isdigit(string[i])) return 0;
    }
    return string[i] == '\n';
}

int betterScanInt() {
    int num;
    char buffer[STR_MAX_LENGTH];
    while (1) {
        if (fgets(buffer, STR_MAX_LENGTH, stdin)) {
            if (isAllDigits(buffer)) {
                sscanf(buffer, "%d", &num);
                return num;
            }
        }
        printf("Not an integer! Enter a valid integer\n");
    }
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

void printIntArray(const int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void initIntArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter int for index %d:\n", i);
        scanf(" %d", &arr[i]);
    }
}

void reverseArray(int *arr, int size) {
    int right = size - 1;
    for (int left = 0; left < right; left++, right--) {
        int temp = *(arr + right);
        *(arr + right) = *(arr + left);
        *(arr + left) = temp;
    }
}


// Generic implementation of swap - go over bytes and swap
void swap(void *a, void *b, int typeSize) {
    char temp;
    char *first = (char *) a;
    char *second = (char *) b;

    for (int i = 0; i < typeSize; i++) {
        temp = *(first + i);
        *(first + i) = *(second + i);
        *(second + i) = temp;
    }
}

// Generic implementation of swap - just copy memory
void swap2(void *a, void *b, int typeSize) {
    char *temp = (char *) malloc(typeSize);

    memcpy(temp, a, typeSize);
    memcpy(a, b, typeSize);
    memcpy(b, temp, typeSize);

    free(temp);
}

/*
 * print array of any type
 * -----------------------------
 * Usage:
 *
 *      void printInt(void *num) {
 *        int *n = (int *) num;
 *        printf("%d ", *n);
 *      }
 *
 *      printArr(numbers, SIZE, sizeof(int), printInt);
 */
void printArr(void *arr, int size, int typeSize, void (*print)(void *)) {
    for (int i = 0; i < size; i++) {
        print((char *) arr + i * typeSize);
        printf(" ");
    }
    printf("\n");
}

//int scanInt() {
//    int num;
//    char term;
//    while (1) {
//        if (scanf("%d%c", &num, &term) != 2 || term != '\n') {
//            printf("Not an integer! Enter a valid integer\n");
//            getchar(); //clear buffer
//        } else return num;
//    }

//}


void cleanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

}

void trim(char *str) {
    char *end;

    while (isspace((unsigned char) *str)) str++;

    if (*str == 0) return;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;
    end[1] = '\0';
}

int isAllLetters(const char *str) {
    unsigned char c;
    while ((c = *str) && (isalpha(c) || isblank(c))) ++str;
    return *str == '\0';
}