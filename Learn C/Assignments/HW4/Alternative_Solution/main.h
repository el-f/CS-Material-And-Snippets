#pragma once

typedef enum
{
	eAddFlight, eAddAirport, ePrintCompany, ePrintAirports,ePrintFlightOrigDest,
	eSortFlights, eSearchFlight,
	eNofOptions
} eMenuOptions;

const char* str[eNofOptions];

#define EXIT			-1

int menu();
int initManagerAndCompany(AirportManager* pManager,const char* managerFileName,
			Company* pCompany,const char* companyFileName);