#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "Utils.h"

int isAllDigits(char *string) {
    int i;
    for (i = 0; i < strlen(string) - 1; i++) {
        if (!isdigit(string[i])) return 0;
    }
    return string[i] == '\n';
}

int scanInt() {
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
    char inpStr[STR_MAX_LENGTH]; //var to hold str given by user
    getStr(inpStr, sizeof(inpStr));

    len = strlen(inpStr) + 1; // +1 for '\0'

    theStr = malloc(len * sizeof(char)); //allocate mem
    if (theStr != NULL) strcpy(theStr, inpStr); //fill mem

    return theStr;
}

void strToUpper(char *str) {
    for (; *str; ++str) *str = toupper(*str);
}

void strToLower(char *str) {
    for (; *str; ++str) *str = tolower(*str);
}

int isAllLetters(const char *str) {
    unsigned char c;
    while ((c = *str) && (isalpha(c) || isblank(c))) ++str;
    return *str == '\0';
}

char *getValidIATA(char dir[]) {
    bool success = false;
    char *IATA;
    do {
        printf("Please enter %s IATA (all letters and length of 3, will convert to uppercase automatically):\n", dir);
        IATA = getStrAuto();
        if (!IATA) return NULL;

        if (strlen(IATA) == 3 && isAllLetters(IATA)) {
            strToUpper(IATA);
            success = true;
        }
    } while (!success);
    return IATA;
}

void trim(char *str) {
    char *end;

    while (isspace((unsigned char) *str)) str++;

    if (*str == 0) return;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;
    end[1] = '\0';
}

void capitalizeFirstWords(char *string) {
    strToLower(string);

    char *last_space = strrchr(string, ' ');
    if (last_space == NULL) last_space = string + strlen(string);

    bool newWord = true;
    for (int i = 0; i < strlen(string); i++) {
        if ((string + i) >= last_space) break;
        if (newWord) {
            string[i] = toupper(string[i]);
            newWord = false;
        }
        if (isspace(string[i])) newWord = true;
    }
}

void alternateCapitalization(char *string) {
    for (int i = 0; i < strlen(string); i++) {
        if (i % 2 == 0) string[i] = toupper(string[i]);
        else string[i] = tolower(string[i]);
    }
}

#define SPACE_DELIMITER " "
#define NEW_SPACE "  "

char *doubleSpacesAndAlternateCaps(char *string) {
    char *copy = malloc(1);
    memset(copy, 0, 1); //easy way to ensure null terminator
    if (copy == NULL) return NULL;

    char *token = strtok(string, SPACE_DELIMITER);
    while (token != NULL) {
        if (strlen(token) % 2 == 0) alternateCapitalization(token);

        copy = realloc(copy, strlen(copy) + strlen(token) + strlen(NEW_SPACE) + 1);
        if (!copy) return NULL;
        strcat(copy, token);

        token = strtok(NULL, SPACE_DELIMITER);

        if (token != NULL) strcat(copy, NEW_SPACE);

    }
    free(string);
    return copy;
}