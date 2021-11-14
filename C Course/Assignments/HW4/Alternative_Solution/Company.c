#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "Company.h"
#include "Airport.h"
#include "General.h"
#include "fileHelper.h"
#include "myMacros.h"

static const char* sortOptStr[eNofSortOpt] = {
	"None","Hour", "Date", "Airport takeoff code", "Airport landing code" };


int	initCompanyFromFile(Company* pComp, AirportManager* pManaer, const char* fileName)
{
	L_init(&pComp->flighDateList);
	if (loadCompanyFromFile(pComp, pManaer, fileName))
	{
		initDateList(pComp);
		return 1;
	}
	return 0;
}

void	initCompany(Company* pComp,AirportManager* pManaer)
{
	printf("-----------  Init Airline Company\n");
	L_init(&pComp->flighDateList);
	
	pComp->name = getStrExactName("Enter company name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	pComp->sortOpt = eNofSortOpt;
}

void	initDateList(Company* pComp)
{	
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if(isUniqueDate(pComp,i))
		{
			char* sDate = createDateString(&pComp->flightArr[i]->date);
			L_insert(&(pComp->flighDateList.head), sDate);
		}
	}
}

int		isUniqueDate(const Company* pComp, int index)
{
	Date* pCheck = &pComp->flightArr[index]->date;
	for (int i = 0; i <index; i++)
	{
		if (equalDate(&pComp->flightArr[i]->date,pCheck))
			return 0;
	}
	return 1;
}

int		addFlight(Company* pComp, const AirportManager* pManager)
{

	if (pManager->count < 2)
	{
		printf("There are not enoght airport to set a flight\n");
		return 0;
	}
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
	CHECK_RETRUN_0(pComp->flightArr);

	pComp->flightArr[pComp->flightCount] = (Flight*)calloc(1, sizeof(Flight));
	
	CHECK_RETRUN_0(pComp->flightArr[pComp->flightCount]);
	
	initFlight(pComp->flightArr[pComp->flightCount], pManager);
	if (isUniqueDate(pComp, pComp->flightCount))
	{
		char* sDate = createDateString(&pComp->flightArr[pComp->flightCount]->date);
		L_insert(&(pComp->flighDateList.head), sDate);
	}
	pComp->flightCount++;
	return 1;
}

void	printCompany(const Company* pComp,char* str,...)
{
	va_list strList;

	va_start(strList, str);
	char*	longName = catStrings(pComp->name,str, strList);

	printf("Company %s\n",longName);
	free(longName);
	printf("Has %d flights\n", pComp->flightCount);
#ifdef DETAIL_PRINT
	generalArrayFunction((void*)pComp->flightArr, pComp->flightCount, sizeof(Flight**), printFlightV);
	printf("\nFlight Date List:");
	L_print(&pComp->flighDateList, printStr);
#endif
}

void	printFlightsCount(const Company* pComp)
{
	char codeOrigin[CODE_LENGTH + 1];
	char codeDestination[CODE_LENGTH + 1];

	if (pComp->flightCount == 0)
	{
		printf("No flight to search\n");
		return;
	}

	printf("Origin Airport\n");
	getAirportCode(codeOrigin);
	printf("Destination Airport\n");
	getAirportCode(codeDestination);

	int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
	if (count != 0)
		printf("There are %d flights ", count);
	else
		printf("There are No flights ");

	printf("from %s to %s\n", codeOrigin, codeDestination);
}

int		saveCompanyToFile(const Company* pComp, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "wb");

	CHECK_MSG_RETURN_0(fp, "Error open copmpany file to write\n");
	int res;
#ifndef COMP_SAVE
	res =  saveCompanyDataToFile(pComp, fp);
#else
	res =  saveCompressCompanyDataToFile(pComp, fp);
#endif
	fclose(fp);
	return res;
}

int	saveCompanyDataToFile(const Company* pComp,FILE* fp)
{

	if (!writeStringToFile(pComp->name, fp, "Error write comapny name\n"))
		return 0;

	if (!writeIntToFile(pComp->flightCount, fp, "Error write flight count\n"))
		return 0;

	if (!writeIntToFile((int)pComp->sortOpt, fp, "Error write sort option\n"))
		return 0;

	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (!saveFlightToFile(pComp->flightArr[i], fp))
			return 0;
	}
	
	return 1;
}

int	saveCompressCompanyDataToFile(const Company* pComp, FILE* fp)
{
	BYTE data[2];

	data[0] =	(pComp->flightCount & 0X1) << 7 | 
				(pComp->sortOpt & 0x7) << 4		|
				(strlen(pComp->name) & 0xF);
	data[1] = (pComp->flightCount >> 1) & 0xFF;
	

	if (fwrite(data, sizeof(BYTE), 2, fp) != 2)
		MSG_CLOSE_RETURN_0(fp, "Error write flight count, sort option and name length\n");

	int length = (int)strlen(pComp->name) + 1;
	if (fwrite(pComp->name, sizeof(char), length, fp) != length)
		MSG_CLOSE_RETURN_0(fp, "Error write company name\n");

	for (int i = 0; i < pComp->flightCount; i++)
		CHECK_0_MSG_CLOSE_FILE(saveCompressFlightToFile(pComp->flightArr[i], fp), fp, "Error write flight\n");

	return 1;

}

int loadCompanyFromFile(Company* pComp, const AirportManager* pManager, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");

	CHECK_MSG_RETURN_0(fp, "Error open company file\n");

	pComp->flightArr = NULL;

	int res;
#ifndef COMP_LOAD
	res = loadCompanyDataToFile(pComp, pManager, fp);
#else
	res = loadCompressCompanyDataToFile(pComp, pManager, fp);
#endif
	fclose(fp);
	return res;
}

int loadCompanyDataToFile(Company* pComp, const AirportManager* pManager, FILE* fp)
{
	pComp->name = readStringFromFile(fp, "Error reading company name\n");
	CHECK_RETRUN_0(pComp->name);
	

	if (!readIntFromFile(&pComp->flightCount, fp, "Error reading flight count name\n"))
		return 0;

	int opt;
	if (!readIntFromFile(&opt, fp,"Error reading sort option\n"))
		return 0;

	pComp->sortOpt = (eSortOption)opt;

	if (pComp->flightCount > 0)
	{
		pComp->flightArr = (Flight**)malloc(pComp->flightCount * sizeof(Flight*));
		CHECK_NULL_MSG_COLSE_FILE(pComp->flightArr, fp, "Alocation error\n");
	}
	else
		pComp->flightArr = NULL;

	for (int i = 0; i < pComp->flightCount; i++)
	{
		pComp->flightArr[i] = (Flight*)calloc(1, sizeof(Flight));
		CHECK_NULL_MSG_COLSE_FILE(pComp->flightArr[i], fp, "Alocation error\n");
		if (!loadFlightFromFile(pComp->flightArr[i], pManager, fp))
			return 0;
	}
	return 1;
}


int loadCompressCompanyDataToFile(Company* pComp, const AirportManager* pManager, FILE* fp)
{

	BYTE data[2];

	if (fread(data, sizeof(BYTE), 2, fp) != 2)
		MSG_CLOSE_RETURN_0(fp, "Error reading flight count, sort option and name length\n");


	pComp->flightCount = (data[1] <<1) | (data[0] >> 7) & 0X1;
	pComp->sortOpt = (data[0] >> 4) & 0x7;
	
	int length = (data[0] & 0xF)+1;



	pComp->name = (char*)malloc(length* sizeof(char));
	CHECK_NULL_MSG_COLSE_FILE(pComp->name, fp, "Alloction error\n");

	if (fread(pComp->name, sizeof(char), length, fp) != length)
		MSG_CLOSE_RETURN_0(fp, "rror reading name\n");

	if (pComp->flightCount > 0)
	{
		pComp->flightArr = (Flight**)malloc(pComp->flightCount * sizeof(Flight*));
		CHECK_NULL_MSG_COLSE_FILE(pComp->flightArr, fp, "Alloction error\n");
	}
	else
		pComp->flightArr = NULL;


	for (int i = 0; i < pComp->flightCount; i++)
	{
		pComp->flightArr[i] = (Flight*)calloc(1, sizeof(Flight));
		CHECK_NULL_MSG_COLSE_FILE(pComp->flightArr[i], fp, "Alloction error\n");
		CHECK_0_MSG_CLOSE_FILE(loadCompressFlightFromFile(pComp->flightArr[i], pManager, fp), fp, "Alloction error\n");
	}
	return 1;

}

void	sortFlight(Company* pComp)
{
	pComp->sortOpt = showSortMenu();
	int(*compare)(const void* air1, const void* air2) = NULL;

	switch (pComp->sortOpt)
	{
	case eHour:
		compare = compareByHour;
		break;
	case eDate:
		compare = compareByDate;
		break;
	case eSorceCode:
		compare = compareByCodeOrig;
		break;
	case eDestCode:
		compare = compareByCodeDest;
		break;
	
	}

	if (compare != NULL)
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compare);

}

void	findFlight(const Company* pComp)
{
	int(*compare)(const void* air1, const void* air2) = NULL;
	Flight f = { 0 };
	Flight* pFlight = &f;


	switch (pComp->sortOpt)
	{
	case eHour:
		f.hour = getFlightHour();
		compare = compareByHour;
		break;
	case eDate:
		getchar();
		getCorrectDate(&f.date);
		compare = compareByDate;
		break;
	case eSorceCode:
		getchar();
		getAirportCode(f.originCode);
		compare = compareByCodeOrig;
		break;
	case eDestCode:
		getchar();
		getAirportCode(f.destCode);
		compare = compareByCodeDest;
		break;
	}

	if (compare != NULL)
	{
		Flight** pF = bsearch(&pFlight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compare);
		if (pF == NULL)
			printf("Flight was not found\n");
		else {
			printf("Flight found, ");
			printFlight(*pF);
		}
	}
	else {
		printf("The search cannot be performed, array not sorted\n");
	}

}

eSortOption showSortMenu()
{
	int opt;
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 1; i < eNofSortOpt; i++)
			printf("Enter %d for %s\n", i, sortOptStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >eNofSortOpt);

	return (eSortOption)opt;
}

void	freeCompany(Company* pComp)
{
	generalArrayFunction((void*)pComp->flightArr, pComp->flightCount, sizeof(Flight**), freeFlight);
	free(pComp->flightArr);
	free(pComp->name);
	L_free(&pComp->flighDateList, freePtr);
}
