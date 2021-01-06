#ifndef __FLIGHT__
#define __FLIGHT__

#include "AirportManager.h"
#include "Date.h"
#include "General.h"

typedef struct {
    char originCode[CODE_LENGTH + 1];
    char destCode[CODE_LENGTH + 1];
    int hour;
    Date date;
} Flight;

void initFlight(Flight *pFlight, const AirportManager *pManager);

int isFlightInRoute(const Flight *pFlight, const char *codeSource, const char *codeDest);

int countFlightsInRoute(Flight **arr, int size, const char *codeSource, const char *codeDest);

void printFlight(void *pFlight);

int getFlightHour();

Airport *setAirportToFlight(const AirportManager *pManager, const char *msg);

void freeFlight(void *pFlight);

int compareFlightsByHour(const void *flight1, const void *flight2);

int compareFlightsByDate(const void *flight1, const void *flight2);

int compareFlightsByOriginAirport(const void *flight1, const void *flight2);

int compareFlightsByDestinationAirport(const void *flight1, const void *flight2);

int writeFlightToBinFile(FILE *fp, const Flight *flight);

int readFlightFromBinFile(FILE *fp, Flight *flight);

#endif
