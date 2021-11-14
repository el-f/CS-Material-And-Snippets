#ifndef __AIRPORT__
#define __AIRPORT__

typedef struct {
    char *name;
    char *country;
    char *IATA;
} Airport;

int areAirportsEqual(const char *IATA1, const char *IATA2);

int isIATAOfAirport(const char *IATA, const Airport *airport);

Airport initAirport();

void printAirport(const Airport *airport);

void freeAirport(Airport *airport);

int initIATA(Airport *airport);

char *processAirportName(char *name);

#endif //__AIRPORT__
