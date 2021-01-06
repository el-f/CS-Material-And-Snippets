#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"

typedef enum {
    unsorted,
    sortedByHour,
    sortedByDate,
    sortedByOriginAirport,
    sortedByDestinationAirport,
    eNofSortOptions
} flightSortOption;

const char *printableSortOptions[eNofSortOptions];

typedef struct {
    char *name;
    int flightCount;
    Flight **flightArr;
    LIST flightDates;
    flightSortOption currentSort;
} Company;

void initCompany(Company *pComp);

int addFlight(Company *pComp, const AirportManager *pManager);

void printCompany(const Company *pComp);

void printFlightsCount(const Company *pComp);

void freeCompany(Company *pComp);

int addDateToList(Company *pComp, Date *date);

int (*chooseCompareFunction(Company *pComp))(const void *, const void *);

void sortFlights(Company *pComp);

void searchFlight(Company *pComp);

int writeCompanyToBinFile(FILE *fp, const Company *pComp);

int readCompanyFromBinFile(FILE *fp, Company *pComp);

void generalArrayFunction(void *array, int arraySize, int elementSize, void (*function)(void *));

#endif

