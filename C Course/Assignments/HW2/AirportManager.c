#include <malloc.h>
#include <stdio.h>

#include "AirportManager.h"
#include "Utils.h"

char *getExistingIATA(const AirportManager *airportManager, int origin) {
    bool success = false;
    char *IATA;
    Airport *foundAirport;
    do {
        IATA = getValidIATA(origin ? ORIGIN : DESTINATION);
        if (!IATA) return NULL;

        foundAirport = findAirport(airportManager, IATA);
        if (foundAirport == NULL) {
            printf("No airport with such IATA!\n");
        } else {
            success = true;
        }
    } while (!success);

    return IATA;
}

int addAirport(AirportManager *airportManager) {
    Airport *airports = realloc(
            airportManager->airports,
            sizeof(Airport) * (airportManager->numOfAirports + 1)
    );
    if (!airports) return 0;
    airportManager->airports = airports;

    Airport airport;
    bool success;
    do {
        airport = initAirport();
        if (airport.IATA == 0) {
            printf("Invalid airport initialization!\n");
        } else {
            success = (airportManager->numOfAirports == 0 ? 1 : findAirport(airportManager, airport.IATA) == NULL);
        }
        if (!success) printf("Airport with such IATA already exists! Enter airport again!\n");
    } while (!success);

    airportManager->airports[airportManager->numOfAirports] = airport;
    airportManager->numOfAirports++;
    return 1;
}

Airport *findAirport(const AirportManager *airportManager, const char *IATA) {
    for (int i = 0; i < airportManager->numOfAirports; i++) {
        if (isIATAOfAirport(IATA, &airportManager->airports[i]))
            return &airportManager->airports[i];
    }
    return NULL;
}

int initAirportManager(AirportManager *airportManager) {
    printf("Initializing Airport Manager...\n");
    int numOfAirports;
    do {
        printf("Please enter number of airports to initialize:\n");
        numOfAirports = scanInt();
        if (numOfAirports < 2) {
            printf("At least 2 airports are needed!\n");
        }
    } while (numOfAirports < 2);

    airportManager->airports = malloc(sizeof(Airport) * numOfAirports);
    airportManager->numOfAirports = 0;

    for (int i = 0; i < numOfAirports; i++) {
        printf("Initializing Airport %d:\n", i + 1);
        if (!addAirport(airportManager)) return 0;
    }

    return 1;
}

void printAirportManager(const AirportManager *airportManager) {
    for (int i = 0; i < airportManager->numOfAirports; i++) {
        printAirport(&airportManager->airports[i]);
    }
}

void freeAirportManager(AirportManager *airportManager) {
    for (int i = 0; i < airportManager->numOfAirports; i++) {
        freeAirport(&airportManager->airports[i]);
    }
    free(airportManager->airports);
}