#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "Airline.h"
#include "Utils.h"

int addFlight(Airline *airline, const AirportManager *airportManager) {
    Flight **flights = realloc(airline->flights, sizeof(Flight *) * (airline->numOfFlights + 1));
    if (!flights) return 0;
    airline->flights = flights;

    Flight *flight = malloc(sizeof(Flight));
    initFlight(airportManager, flight);
    if (!flight) return 0;

    airline->flights[airline->numOfFlights++] = flight;

    return 1;
}

void printNumOfFlightsInLine(const Airline *airline, const AirportManager *airportManager) {
    if (airline->numOfFlights == 0) {
        printf("No flights exist for the airline!\n");
        return;
    }

    char *originIATA = getExistingIATA(airportManager, true);
    if (!originIATA) {
        printf("Malloc Error!\n");
        return;
    }

    char *destinationIATA = getExistingIATA(airportManager, false);
    if (!destinationIATA) {
        printf("Malloc Error!\n");
        return;
    }

    if (areAirportsEqual(originIATA, destinationIATA)) {
        printf("Invalid line! destination same as origin!\n");
        return;
    }

    int count = countFlightsInLine((const Flight **) airline->flights, airline->numOfFlights, originIATA, destinationIATA);
    printf("There %s %d flight%s from %s to %s\n",
           (count == 1 ? "is" : "are"),
           count,
           (count == 1 ? "" : "s"),
           originIATA,
           destinationIATA
    );
}

int initAirline(Airline *airline) {
    printf("\nInitializing Airline...\n");
    airline->flights = malloc(0);
    if (!airline->flights) return 0;

    airline->numOfFlights = 0;

    printf("Enter airline name:\n");
    airline->name = getStrAuto();
    if (!airline->name) return 0;
    if (strlen(airline->name) == 0) {
        printf("Empty airline name!\n");
        return 0;
    }

    return 1;
}

void printAirline(const Airline *airline) {
    if (airline->numOfFlights == 0) {
        printf("No flights exist for the airline!\n");
        return;
    }
    printf("Airline %s:\n", airline->name);
    for (int i = 0; i < airline->numOfFlights; i++) {
        printFlight(airline->flights[i]);
    }
}

void freeAirline(Airline *airline) {
    for (int i = 0; i < airline->numOfFlights; i++) {
        freeFlight(airline->flights[i]);
        free(airline->flights[i]);
    }
    free(airline->flights);
    free(airline->name);
}