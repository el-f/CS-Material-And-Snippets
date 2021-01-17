#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

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
    char buffer[10]; // 10 - max length of integer (2,147,483,647)
    while (1) {
        if (fgets(buffer, 10, stdin)) {
            if (isAllDigits(buffer)) {
                sscanf(buffer, "%d", &num);
                return num;
            }
        }
        printf("Not an integer! Enter a valid integer\n");
    }
}

char scanChar() {
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

#define MAX_LENGTH 255

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

void generalArrayFunction(void *arr, int size, int typeSize, void(*func)(void *element)) {
    for (int i = 0; i < size; i++)
        func((char *) (arr) + i * typeSize);

}

char **splitCharsToWords(char *str, int *pCount, int *pTotalLength) {
    char temp[255];
    char *delimiters = " ";
    char *word;
    int count = 0;

    strcpy(temp, str);
    char **wordsArray = NULL;
    *pTotalLength = 0;

    word = strtok(temp, delimiters);
    while (word != NULL) {
        wordsArray = (char **) realloc(wordsArray, (count + 1) * sizeof(char *));
        if (!wordsArray)
            return 0;
        wordsArray[count] = getDynStr(word);
        count++;
        *pTotalLength += (int) strlen(word);
        word = strtok(NULL, delimiters);
    }
    *pCount = count;
    return wordsArray;
}

char *myGets(char *buffer, int size, FILE *fp) {
    if (buffer != NULL && size > 0) {
        if (fgets(buffer, size, fp)) {
            buffer[strcspn(buffer, "\n")] = '\0';
            return buffer;
        }
        buffer[0] = '\0';
    }
    return NULL;
}

char *getStrAutoFromFile(FILE *fp) {
    char *theStr = NULL;
    int len;
    char inpStr[MAX_LENGTH]; //var to hold str that user gives
    myGets(inpStr, sizeof(inpStr), fp);

    len = strlen(inpStr) + 1; // +1 for '\0'

    theStr = malloc(len * sizeof(char)); //allocate mem
    if (theStr != NULL) strcpy(theStr, inpStr); //fill mem

    return theStr;
}

char *getDynStr(char *str) {
    char *theStr;
    theStr = (char *) malloc((strlen(str) + 1) * sizeof(char));
    if (!theStr)
        return NULL;

    strcpy(theStr, str);
    return theStr;
}

char *getStrExactName(const char *msg, FILE *fp) {
    char *str;
    char temp[MAX_LENGTH];
    printf("%s\t", msg);
    myGets(temp, MAX_LENGTH, fp);

    str = getDynStr(temp);
    return str;
}

int writeStringToFile(char *str, FILE *fp, const char *msg) {
    int length = strlen(str);
    length++;
    if (!writeIntToFile(length, fp, msg))
        return 0;

    if (!writeCharsToFile(str, length, fp, msg))
        return 0;


    return 1;
}

int writeCharsToFile(char *arr, int size, FILE *fp, const char *msg) {
    if (fwrite(arr, sizeof(char), size, fp) != size) {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;

}

int writeIntToFile(int val, FILE *fp, const char *msg) {
    if (fwrite(&val, sizeof(int), 1, fp) != 1) {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;
}

char *readStringFromFile(FILE *fp, const char *msg) {
    char *str;
    int length;
    if (!readIntFromFile(&length, fp, msg))
        return NULL;
    str = (char *) malloc((length) * sizeof(char));
    if (!str) {
        puts(msg);
        fclose(fp);
        return NULL;
    }
    if (fread(str, sizeof(char), length, fp) != length) {
        puts(msg);
        fclose(fp);
        return NULL;
    }
    return str;

}

int readCharsFromFile(char *arr, int length, FILE *fp, const char *msg) {
    if (fread(arr, sizeof(char), length, fp) != length) {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;
}

int readIntFromFile(int *pVal, FILE *fp, const char *msg) {
    if (fread(pVal, sizeof(int), 1, fp) != 1) {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;

}

int isValidDate(int day, int month, int year) {
    //check year
    if (year >= 1900 && year <= 2100) {
        //check month
        if (month >= 1 && month <= 12) {
            //check days
            if (((day >= 1 && day <= 31) &&
                 (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
                || ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11))
                || ((day >= 1 && day <= 28) && (month == 2))
                || ((day == 29 && month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))))) {
                return true;
            } else printf("Invalid Day!\n");
        } else printf("Invalid Month!\n");
    } else printf("Invalid Year!\n");

    return false;
}

