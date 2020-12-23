#ifndef __FLIGHT__
#define __FLIGHT__

#include "Airport.h"
#include "Date.h"
#include "AirportManager.h"

typedef struct {
    char *originIATA;
    char *destinationIATA;
    Date date;
    int hour;
} Flight;

int isCorrelatingFlight(const Flight *flight, const char *originIATA, const char *destinationIATA);

int countFlightsInLine(const Flight **flights, int size, const char *originIATA, const char *destinationIATA);

int initFlight(const AirportManager *airportManager, Flight *flight);

void printFlight(const Flight *flight);

void freeFlight(Flight *flight);

#endif //__FLIGHT__
