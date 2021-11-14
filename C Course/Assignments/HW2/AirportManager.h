#ifndef __AIRPORT_MANAGER__
#define __AIRPORT_MANAGER__

#include "Airport.h"

typedef struct {
    Airport *airports;
    int numOfAirports;
} AirportManager;

char *getExistingIATA(const AirportManager *airportManager, int origin);

int addAirport(AirportManager* airportManager);

Airport *findAirport(const AirportManager* airportManager, const char* IATA);

int initAirportManager(AirportManager *airportManager);

void printAirportManager(const AirportManager *airportManager);

void freeAirportManager(AirportManager *airportManager);

#endif //__AIRPORT_MANAGER__
