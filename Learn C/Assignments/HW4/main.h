#pragma once

typedef enum {
    eAddFlight, eAddAirport, ePrintCompany, ePrintAirports, ePrintFlightOrigDest,
    eSortFlights, eSearchFlight,
    eNofOptions
} eMenuOptions;

const char *str[eNofOptions];

#define EXIT            (-1)

int menu();

int initManagerAndCompany(AirportManager *pManager, Company *pCompany, const char *managerFileName,
                          const char *companyFileName);