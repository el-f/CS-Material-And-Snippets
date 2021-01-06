#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "Airport.h"
#include "General.h"


int isSameAirport(const Airport *pPort1, const Airport *pPort2) {
    if (!pPort1 || !pPort2)
        return 0;
    if (strcmp(pPort1->code, pPort2->code) == 0)
        return 1;

    return 0;
}

int isAirportCode(const Airport *pPort1, const char *code) {
    if (!pPort1)
        return 0;
    if (strcmp(pPort1->code, code) == 0)
        return 1;

    return 0;
}

void initAirportNoCode(Airport *pPort) {
    getAirportName(pPort);
    pPort->country = getStrExactName("Enter airport country");
}

void printAirport(const void *pPort) {
    const Airport *airport = (const Airport *) pPort;
    printf("Airport name:%-20s\t", airport->name);
    printf("Country: %-20s\t Code:%s\n", airport->country, airport->code);

}

void getAirportName(Airport *pPort) {
    char temp[255];
    char **wordsArray = NULL;
    int totalLength;
    int count;

    printf("Enter airport name\t");
    myGets(temp, MAX_STR_LEN);

    wordsArray = splitCharsToWords(temp, &count, &totalLength);
    pPort->name = (char *) calloc(totalLength + (count - 1) * 2 + 1, sizeof(char));
    if (!pPort->name) {
        for (int i = 0; i < count; i++)
            free(wordsArray[i]);
        free(wordsArray);
        return;
    }
    int len;
    for (int i = 0; i < count; i++) {
        len = (int) strlen(wordsArray[i]);
        if (len % 2 == 0) //even number of letters
            changeEvenWord(wordsArray[i]);
        else {
            if (i == count - 1 && count > 1) //last but not only!
                wordsArray[i][0] = tolower(wordsArray[i][0]); //small
            else
                wordsArray[i][0] = toupper(wordsArray[i][0]); //big
        }
        strcat(pPort->name, wordsArray[i]);
        if (i != count - 1) //not last
            strcat(pPort->name, "  ");
    }

    //clean temp data
    for (int i = 0; i < count; i++)
        free(wordsArray[i]);
    free(wordsArray);
}

void changeEvenWord(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
        *str = tolower(*str);
        str++;
    }
}

void getAirportCode(char *code) {
    char temp[MAX_STR_LEN];
    int ok = 1;
    do {
        ok = 1;
        printf("Enter airport code  - %d UPPER CASE letters\t", CODE_LENGTH);
        myGets(temp, MAX_STR_LEN);
        if (strlen(temp) != CODE_LENGTH) {
            printf("code should be %d letters\n", CODE_LENGTH);
            ok = 0;
        } else {
            for (int i = 0; i < 3; i++) {
                if (isupper(temp[i]) == 0) {
                    printf("Need to be upper case letter\n");
                    ok = 0;
                    break;
                }
            }
        }
    } while (!ok);

    strcpy(code, temp);
}

int compareAirportsByCode(const void *ap1, const void *ap2) {
    return strcmp(
            ((const Airport *) ap1)->code,
            ((const Airport *) ap2)->code
    );
}

void freeAirport(void *pPort) {
    const Airport *airport = (const Airport *) pPort;
    free(airport->name);
    free(airport->country);
}

void writeAirportToTextFile(FILE *fp, const Airport *airport) {
    fprintf(fp, "%s\n%s\n%s\n", airport->name, airport->country, airport->code);
}

int readAirportFromTextFile(FILE *fp, Airport *airport) {
    char buf[MAX_STR_LEN];

    char tav;
    fscanf(fp, "%c", &tav); // clear buffer from '\n'

    if (!fgets(buf, MAX_STR_LEN, fp)) return 0;

    airport->name = _strdup(buf);
    airport->name[strlen(airport->name) - 1] = 0; //remove '\n'

    if (fscanf(fp, "%s", buf) != 1) return 0;
    airport->country = _strdup(buf);

    if (fscanf(fp, "%s", airport->code) != 1) return 0;

    return 1;
}
