#include <string.h>
#include <stdio.h>
#include <malloc.h>

#include "Airport.h"
#include "Utils.h"

int initIATA(Airport *airport) {
    char *IATA = getValidIATA(NO_DIR);
    if (!IATA) return 0;
    airport->IATA = IATA;
    return 1;
}

int areAirportsEqual(const char *IATA1, const char *IATA2) {
    return strcmp(IATA1, IATA2) == 0;
}

int isIATAOfAirport(const char *IATA, const Airport *airport) {
    return areAirportsEqual(IATA, airport->IATA);
}

Airport initAirport() {
    Airport airport = {0, 0, 0};
    printf("Please enter name of the airport:\n");
    char *name = getStrAuto();
    if (!name) return airport;
    if (strlen(name) == 0) {
        printf("Empty name!\n");
        return airport;
    }
    airport.name = processAirportName(name);

    printf("Please enter country of the airport:\n");
    char *country = getStrAuto();
    if (!country) return airport;
    if (strlen(country) == 0) {
        printf("Empty country!\n");
        return airport;
    }
    airport.country = country;

    initIATA(&airport);
    return airport;
}

void printAirport(const Airport *airport) {
    printf("Airport: %s | %-16s | %-16s\n", airport->IATA, airport->name, airport->country);
}

void freeAirport(Airport *airport) {
    free(airport->country);
    free(airport->name);
    free(airport->IATA);
}

char *processAirportName(char *name) {
    trim(name);
    capitalizeFirstWords(name);
    return doubleSpacesAndAlternateCaps(name);
}