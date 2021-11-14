#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "General.h"
#include "Date.h"

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };


void getCorrectDate(Date* pDate)
{
	char date[MAX_STR_LEN];
	int ok = 1;

	do {
		puts("Enter Flight Date dd/mm/yyyy\t");
		myGets(date, MAX_STR_LEN, stdin);
		ok = checkDate(date, pDate);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}


int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	if (strlen(date) != 10)
		return 0;
	if ( (date[2] != '/') || (date[5] != '/'))
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

void printDate(const Date* pDate)
{
	printf("Date: %02d/%02d/%4d\t", pDate->day, pDate->month, pDate->year);
}

char*  createDateString(const Date* pDate)
{
	char str[MAX_STR_LEN];
	sprintf(str,"Date: %02d/%02d/%4d\t", pDate->day, pDate->month, pDate->year);

	return getDynStr(str);
}

int		 equalDate(const Date* pDate1, const Date* pDate2)
{
	if (pDate1->year == pDate2->year &&
		pDate1->month == pDate2->month &&
		pDate1->day == pDate2->day)
		return 1;
	return 0;

}