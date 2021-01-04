#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AirportManager.h"

int	initManager(AirportManager* pManager)
{
	printf("-----------  Init airport Manager\n");
	pManager->count = 0;
	pManager->arr = NULL;

	int count=0;
	do {
		printf("How many airport?\t");
		scanf("%d", &count);
	} while (count < 0);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	if (count == 0)
		return 1;

	pManager->arr = (Airport*)malloc(count * sizeof(Airport));
	if (!pManager->arr)
		return 0;

	for (int i = 0; i < count; i++)
	{
		setAirport(&pManager->arr[i], pManager);
		pManager->count++;
	}
	
	return 1;
}

int	addAirport(AirportManager* pManager)
{
	pManager->arr = (Airport*)realloc(pManager->arr, (pManager->count + 1) * sizeof(Airport));
	if (!pManager->arr)
		return 0;

	setAirport(&pManager->arr[pManager->count], pManager);
	pManager->count++;
	return 1;
}

void  setAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	initAirportNoCode(pPort);
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	for (int i = 0; i < pManager->count; i++)
	{
		if (isAirportCode(&pManager->arr[i], code))
			return &pManager->arr[i];
	}
	return NULL;
}

int checkUniqeCode(const char* code,const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}

void	printAirports(const AirportManager* pManager)
{
	printf("there are %d airports\n", pManager->count);
	for (int i = 0; i < pManager->count; i++)
	{
		printAirport(&pManager->arr[i]);
		printf("\n");
	}
}

void	freeManager(AirportManager* pManager)
{
	free(pManager->arr);
}
