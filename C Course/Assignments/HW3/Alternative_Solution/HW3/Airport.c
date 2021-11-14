#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "Airport.h"
#include "General.h"


int		isSameAirport(const Airport* pPort1, const Airport* pPort2)
{
	if (!pPort1 || !pPort2)
		return 0;
	if (strcmp(pPort1->code, pPort2->code) == 0)
		return 1;

	return 0;
}

int	compareAirport(const void* e1, const void* e2)
{
	Airport* pAir1 = (Airport*)e1;
	Airport* pAir2 = (Airport*)e2;
	return strcmp(pAir1->code, pAir2->code);
}

int		isAirportCode(const Airport* pPort1, const char* code)
{
	if (!pPort1)
		return 0;
	if (strcmp(pPort1->code, code) == 0)
		return 1;

	return 0;
}

void	printAirport(const void* e1)
{
	Airport* pPort = (Airport*)e1;
	printf("Airport name:%-20s\t", pPort->name);
	printf("Country: %-20s\t Code:%s\n", pPort->country,pPort->code);
}

void	initAirportNoCode(Airport* pPort)
{
	getAirportName(pPort);
	pPort->country = getStrExactName("Enter airport country\t");
}

void	getAirportName(Airport* pPort)
{
	char temp[255];

	printf("Enter airport name\t");
	myGets(temp, MAX_STR_LEN, stdin);

	pPort->name = fixName(temp);

}

char* fixName(char* str)
{
	char* name;
	char** wordsArray = NULL;
	int totalLength;
	int count;


	wordsArray = splitCharsToWords(str,&count,&totalLength);
	name = (char*)calloc(totalLength + (count - 1) * 2+1, sizeof(char));
	if (!name)
	{
		for (int i = 0; i < count; i++)
			free(wordsArray[i]);
		free(wordsArray);
		return NULL;
	}
	int len;
	for (int i = 0; i < count; i++)
	{
		len = (int)strlen(wordsArray[i]);
		if (len % 2 == 0) //even number of letters
			changeEvenWord(wordsArray[i]);
		else {
			if(i == count-1 && count > 1) //last but not only!
				wordsArray[i][0] = tolower(wordsArray[i][0]); //small
			else
				wordsArray[i][0] = toupper(wordsArray[i][0]); //big
		}
		strcat(name, wordsArray[i]);
		if(i != count - 1) //not last
			strcat(name, "  ");
	}
	
	//free temp data
	for (int i = 0; i < count; i++)
		free(wordsArray[i]);
	free(wordsArray);
	return name;
}

void	changeEvenWord(char* str)
{
	while (*str)
	{
		*str = toupper(*str);
		str++;
		*str = tolower(*str);
		str++;
	}
}

void getAirportCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter airport code  - %d UPPER CASE letters\t",CODE_LENGTH);
		myGets(temp, MAX_STR_LEN, stdin);
		if (strlen(temp) != CODE_LENGTH)
		{
			printf("code should be %d letters\n",CODE_LENGTH);
			ok = 0;
		}
		else {
			for (int i = 0; i < 3; i++)
			{
				if (isupper(temp[i]) == 0)
				{
					printf("Need to be upper case letter\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);

	strcpy(code, temp);
}

void	freeAirport(void* e1)
{
	Airport* pPort = (Airport*)e1;
	free(pPort->name);
	free(pPort->country);
}

int		saveAirportToFile(const Airport* pAir, FILE* fp)
{
	if (!pAir)
		return 0;
	fprintf(fp, "%s\n", pAir->name);
	fprintf(fp, "%s\n", pAir->country);
	fprintf(fp, "%s\n", pAir->code);
	return 1;
}

int		loadAirportFromFile(Airport* pAir, FILE* fp)
{
	char temp[MAX_STR_LEN];
	if (!pAir)
		return 0;
	do {
		myGets(temp, MAX_STR_LEN, fp);
	} while (strlen(temp) < 2);
	pAir->name = getDynStr(temp);
	do {
		myGets(temp, MAX_STR_LEN, fp);
	} while (strlen(temp) < 2);
	pAir->country = getDynStr(temp);
	fscanf(fp, "%s", pAir->code);
	return 1;
}
