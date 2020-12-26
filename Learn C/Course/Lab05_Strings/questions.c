/*
 * questions.c
 *
 *  Created on: Oct 21, 2018
 *      Author: efrath
 */
#include <stdio.h>
#include <string.h>

#include "questions.h"
#include "stringFunc.h"


void Q1() {
    char str1[MAX_LENGTH];
    char str2[MAX_LENGTH];
    int cmp;

    printf("Lets play with two strings, who is longer who is 'bigger'\n");
    printf("enter a word up to %d chars\n", (MAX_LENGTH - 1));
    scanf("%s", str1);
    printf("The string is:  %s \n", str1);

    getchar(); //clear the buffer from the '\n'

    printf("enter a word up to %d chars\n", (MAX_LENGTH - 1));
    fgets(str2, sizeof(str2), stdin);
    str2[strlen(str2) - 1] = '\0'; // replaces '\n' with string terminator

    puts(str2);

    if (strlen(str1) == strlen(str2)) {
        puts("Equal size strings!");
    } else if (strlen(str1) > strlen(str2)) {
        puts("longer string is:");
        puts(str1);
    } else {
        puts("longer string is:");
        puts(str2);
    }

    cmp = strcmp(str1, str2);
    if (cmp == 0)
        puts("strings are equals");
    else if (cmp < 0)
        printf("%s is smaller \n", str1);
    else
        printf("%s is smaller \n", str2);
}


void Q2() {

    char str[MAX_LENGTH];
    char maxWord[MAX_LENGTH];

    int count;

    printf("Please enter a sentence up to %d letters, you can use capital or small letters\n"
           "Will find the word with most capital letters\n", MAX_LENGTH - 1);
    myGets(str, sizeof(str));

    count = mostCapitalCountWord(str, maxWord);
    if (!count)
        printf("No capital letter word\n");
    else
        printf("The word with most capital letters (%d) is %s\n", count, maxWord);

}


void Q3() {
    char str[] = "What       a beautiful    day!";

    printf("Base string is: %s \n", str);
    fixString(str);

    printf("New string is: %s \n", str);
}

void Q4() {
    int i;

    char strMat[N][MAX_LENGTH];
    arrOfStrings((char *) strMat, N, MAX_LENGTH);

    puts("The strings in the array are:");
    for (i = 0; i < N; i++)
        printf("%s\n", strMat[i]);

}
