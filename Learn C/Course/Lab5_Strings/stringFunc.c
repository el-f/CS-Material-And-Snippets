/*
 * StringFunc.c
 *
 *  Created on: Oct 21, 2018
 *      Author: efrath
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stringFunc.h"


int mostCapitalCountWord(const char *str, char *theWord) {

    char temp[MAX_LENGTH];
    char *delimiters = " ";
    //keep the address of the first char of the next valid word
    char *words;
    //keep the address of the first char of the word with most capitals letters
    char *maxCapitalWord = NULL;
    int maxCount = 0;
    int count;

    //copy to temp  - do not change str
    strcpy(temp, str);
    words = strtok(temp, delimiters);
    while (words != NULL) {
        count = countCapitalLetters(words);
        if (count > maxCount) {
            maxCount = count;
            maxCapitalWord = words;
        }
        words = strtok(NULL, delimiters);
    }

    if (maxCapitalWord != NULL)
        strcpy(theWord, maxCapitalWord);
    return maxCount;
}

int countCapitalLetters(const char *str) {
    int count = 0;
    while (*str) //while(*str != '\0')
    {
        if (isupper(*str)) // if(*str >= 'A' && *str <= 'Z')
            count++;
        str++;
    }
    return count;
}

void fixString(char *str) {
    int noSpace = 1;
    char *pRead = str;
    char *pWrite = str;

    while (*pRead) {
        if (*pRead != ' ') {
            *pWrite = *pRead;
            pWrite++;
            noSpace = 1;
        } else if ((*pRead == ' ') && (noSpace)) {
            *pWrite = *pRead;
            pWrite++;
            noSpace = 0;
        }
        pRead++;
    }
    *pWrite = '\0';
}

void arrOfStrings(char *mat, int rows, int cols) {
    int i;
    int length = 0;
    char *base = mat;

    printf("You will be asked to enter %d strings\n", rows - 1);
    for (i = 0; i < rows - 1; i++) {
        printf("please enter a string\n");
        myGets(mat, cols);
        length += strlen(mat);
        mat += cols;
    }

    *mat = 0;    //mat is pointing now to the last row - init the string to an empty string
    if (length < cols) {
        for (i = 0; i < rows - 1; i++) {
            strcat(mat, base);    //This function copy second string at the end of the first.
            base += cols;
        }
    }
}

int countWords(char *str) {
    int numOfWords = 0;
    while (*str) {
        while (*str && isspace(*str))
            str++;
        if (*str)
            numOfWords++;
        while (*str && !isspace(*str))
            str++;
    }
    return numOfWords;
}

char *myGets(char *buf, size_t size) {
    if (buf != NULL && size > 0) {
        if (fgets(buf, size, stdin)) {
            buf[strcspn(buf, "\n")] = '\0'; //strcspn return index of _control char or str len if char not found
            return buf;
        }
        *buf = '\0';
    }
    return NULL;
}








