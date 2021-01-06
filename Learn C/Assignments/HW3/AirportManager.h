#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"
#include "listGen.h"

typedef struct {
    LIST list;
    int count;
} AirportManager;

int initManager(AirportManager *pManager);

int addAirport(AirportManager *pManager);

void setAirport(Airport *pPort, AirportManager *pManager);

Airport *findAirportByCode(const AirportManager *pManager, const char *code);

int checkUniqueCode(const char *code, const AirportManager *pManager);

void printAirports(const AirportManager *pManager);

void freeManager(AirportManager *pManager);

void writeAirportManagerToTextFile(FILE *fp, const AirportManager *pManager);

int readAirportManagerFromTextFile(FILE *fp, AirportManager *pManager);

#endif