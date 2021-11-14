#ifndef __AIRLINE__
#define __AIRLINE__

#include "Flight.h"

typedef struct {
    char *name;
    int numOfFlights;
    Flight **flights;
} Airline;

int addFlight(Airline *airline, const AirportManager *airportManager);

void printNumOfFlightsInLine(const Airline *airline, const AirportManager *airportManager);

int initAirline(Airline *airline);

void printAirline(const Airline *airline);

void freeAirline(Airline *airline);

#endif //__AIRLINE__
