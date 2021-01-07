#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AirportManager.h"


int	initManager(AirportManager* pManager,const char* fileName)
{
	if (!L_init(&(pManager->airportList)))
		return ERROR;

	if (loadManagerFromFile(pManager, fileName))
		return FROM_FILE;
	
	printf("-----------  Init airport Manager\n");
	pManager->count = 0;


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

	for (int i = 0; i < count; i++)
	{
		if (!addAirport(pManager))
			return 0;
	}
	return FROM_USER;
}

int	addAirport(AirportManager* pManager)
{
	Airport* pPort = createAirport(pManager);
	if (!pPort)
		return 0;

	insertPortToListSorted(&pManager->airportList, pPort);
	pManager->count++;
	return 1;
}

void insertPortToListSorted(LIST* airportList,Airport* pPort)
{
	//insert the new port to list sorted by code
	NODE* tmp = &airportList->head;

	while (tmp->next != NULL)
	{
		if (strcmp(pPort->code, ((Airport*)(tmp->next->key))->code) < 0)
			break; //found the correct place
		tmp = tmp->next;
	}

	L_insert(tmp, pPort);
}



Airport*  createAirport(AirportManager* pManager)
{
	Airport* pPort = (Airport*)calloc(1, sizeof(Airport));
	if (!pPort)
		return NULL;

	while(1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}
	
	initAirportNoCode(pPort);
	return pPort;
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	//create dummy airport with the search code
	Airport temp = { 0 };
	strcpy(temp.code,code);

	//use list find function
	NODE* portNode;
	portNode = L_find(pManager->airportList.head.next, &temp, compareAirport);

	if(portNode != NULL)
		return portNode->key;
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
	L_print(&pManager->airportList, printAirport);
	printf("\n");
}

int		saveManagerToFile(const AirportManager* pManager, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "w");
	if (!fp) {
		printf("Error open airport manager file to write\n");
		return 0;
	}

	fprintf(fp, "%d\n", pManager->count);
	NODE* pNode = pManager->airportList.head.next;
	while(pNode)
	{
		if (!saveAirportToFile(pNode->key, fp))
		{
			printf("Error write airport\n");
			fclose(fp);
			return 0;
		}
		pNode = pNode->next;
	}
	fclose(fp);
	return 1;

}

int		loadManagerFromFile(AirportManager* pManager, const char* fileName)
{
	FILE* fp;

	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("Error open airport manager file\n");
		return 0;
	}

	fscanf(fp, "%d", &pManager->count);

	Airport* pPort;
	for (int i = 0; i < pManager->count; i++)
	{
		pPort = (Airport*)malloc(sizeof(Airport));
		if (!pPort)
			return 0;

		if (!loadAirportFromFile(pPort, fp))
		{
			printf("Error loading airport from file\n");
			fclose(fp);
			return 0;
		}

		insertPortToListSorted(&pManager->airportList, pPort);
	}

	fclose(fp);
	return 1;


}


void	freeManager(AirportManager* pManager)
{
	L_free(&pManager->airportList,freeAirport);
}

