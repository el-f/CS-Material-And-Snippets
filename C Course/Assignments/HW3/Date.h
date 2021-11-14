#ifndef __MYDATE__
#define __MYDATE__

#define MIN_YEAR 2020

typedef struct {
    int day;
    int month;
    int year;
} Date;

void getCorrectDate(Date *pDate);

int checkDate(char *date, Date *pDate);

void printDateString(const void *dateString);

void printDate(const Date *pDate);

char *dateAsString(const Date *date);

int compareDateStrings(const void *dateStr1, const void *dateStr2);

int compareDates(const void *date1, const void *date2);

int writeDateToBinaryFile(FILE *fp, const Date *date);

int readDateFromBinaryFile(FILE *fp, Date *date);

#endif
