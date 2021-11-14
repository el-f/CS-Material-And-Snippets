#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Company.h"
#include "AirportManager.h"
#include "General.h"
#include "main.h"
#include "myMacros.h"

const char* str[eNofOptions] = { "Add Flight", "Add Airport",
"PrintCompany", "Print all Airports",
	"Print flights between origin-destination",
"Sort Flights", "Search Flight" };


int main(int  argc, char*  argv[])
{
	AirportManager	manager;
	Company			company;

	if (argc != 3)
		ERROR_MSG_PAUSE_RETURN_0("Error in main parameters");

	char* managerFileName = argv[1];
	char* companyFileName = argv[2];


	if (!initManagerAndCompany(&manager, managerFileName, &company, companyFileName))
		ERROR_MSG_PAUSE_RETURN_0("Error init company and airport manager");

	

	int option;
	int stop = 0;
	
	do
	{
		option = menu();
		switch (option)
		{
		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;


		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case ePrintCompany:
			printCompany(&company,"Hachi","Babit","Ba","Olam",NULL);
			break;

		case ePrintAirports:
			printAirports(&manager);
			break;
		
		case ePrintFlightOrigDest:
			printFlightsCount(&company);
			break;
		
		case eSortFlights:
			sortFlight(&company);
			break;

		case eSearchFlight:
			findFlight(&company);
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);


	saveManagerToFile(&manager, managerFileName);
	saveCompanyToFile(&company, companyFileName);

	freeManager(&manager);
	freeCompany(&company);

	system("pause");
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for(int i = 0 ; i < eNofOptions ; i++)
		printf("%d - %s\n",i,str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

int initManagerAndCompany(AirportManager* pManager, const char* managerFileName,
	Company* pCompany, const char* companyFileName)
{
	int res = initManager(pManager, managerFileName);
	if (!res)
	{
		printf("error init manager\n");
		return 0;
	}
	
	if (res == FROM_FILE)
	{
		if (!initCompanyFromFile(pCompany, pManager, companyFileName))
			initCompany(pCompany, pManager);
	}
	else
		initCompany(pCompany, pManager);
	return 1;
}