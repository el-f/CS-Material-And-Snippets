#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "General.h"
#include "Date.h"

const int DAY_MONTHS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


void getCorrectDate(Date *pDate) {
    char date[MAX_STR_LEN];
    int ok;

    do {
        puts("Enter Flight Date dd/mm/yyyy\t");
        myGets(date, MAX_STR_LEN);
        ok = checkDate(date, pDate);
        if (!ok)
            printf("Error try again\n");
    } while (!ok);
}

int checkDate(char *date, Date *pDate) {
    int day, month, year;
    if (strlen(date) != 10)
        return 0;
    if ((date[2] != '/') || (date[5] != '/'))
        return 0;
    sscanf(date, "%d/%d/%d", &day, &month, &year);
    if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
        return 0;

    if (day > DAY_MONTHS[month - 1])
        return 0;

    pDate->day = day;
    pDate->month = month;
    pDate->year = year;

    return 1;
}

void printDateString(const void *dateString) {
    printf("%s\n", (const char *) dateString);
}

void printDate(const Date *pDate) {
    printf("Date: %d/%d/%d\t", pDate->day, pDate->month, pDate->year);
}


char *dateAsString(const Date *date) {
    char *dateString = malloc(sizeof(char) * 12);
    sprintf(dateString, "%d/%d/%d\n", date->day, date->month, date->year);
    return dateString;
}

int compareDateStrings(const void *dateStr1, const void *dateStr2) {
    Date date1, date2;
    sscanf(dateStr1, "%d/%d/%d", &date1.day, &date1.month, &date1.year);
    sscanf(dateStr2, "%d/%d/%d", &date2.day, &date2.month, &date2.year);
    return compareDates(&date1, &date2);
}

int compareDates(const void *date1, const void *date2) {
    const Date *d1 = (const Date *) date1;
    const Date *d2 = (const Date *) date2;

    if (d1->year != d2->year)
        return d1->year - d2->year;
    if (d1->month != d2->month)
        return d1->month - d2->month;
    return d1->day - d2->day;
}

int writeDateToBinaryFile(FILE *fp, const Date *date) {
    if (fwrite(&date->day, sizeof(int), 1, fp) != 1) { return 0; }
    if (fwrite(&date->month, sizeof(int), 1, fp) != 1) { return 0; }
    if (fwrite(&date->year, sizeof(int), 1, fp) != 1) { return 0; }

    return 1;
}

int readDateFromBinaryFile(FILE *fp, Date *date) {
    if (fread(&date->day, sizeof(int), 1, fp) != 1) { return 0; }
    if (fread(&date->month, sizeof(int), 1, fp) != 1) { return 0; }
    if (fread(&date->year, sizeof(int), 1, fp) != 1) { return 0; }

    return 1;
}


