#include <malloc.h>
#include <stdio.h>

#include "Flight.h"
#include "Utils.h"

int isCorrelatingFlight(const Flight *flight, const char *originIATA, const char *destinationIATA) {
    return areAirportsEqual(flight->originIATA, originIATA) &&
           areAirportsEqual(flight->destinationIATA, destinationIATA);
}

int countFlightsInLine(const Flight **flights, int size, const char *originIATA, const char *destinationIATA) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        count += isCorrelatingFlight(flights[i], originIATA, destinationIATA);
    }
    return count;
}

int initFlight(const AirportManager *airportManager, Flight *flight) {
    flight->originIATA = getExistingIATA(airportManager, true);
    if (!flight->originIATA) return 0;

    flight->destinationIATA = getExistingIATA(airportManager, false);
    if (!flight->destinationIATA) return 0;

    if (areAirportsEqual(flight->originIATA, flight->destinationIATA)) {
        printf("Invalid flight! destination same as origin!\n");
        return 0;
    }

    flight->date = initDate();
    flight->hour = getValidHour();

    return 1;
}

void printFlight(const Flight *flight) {
    printf(
            "Flight From: %s To: %s on %d/%d/%d at %d O'clock\n",
            flight->originIATA,
            flight->destinationIATA,
            flight->date.day, flight->date.month, flight->date.year,
            flight->hour
    );
}

void freeFlight(Flight *flight) {
    free(flight->originIATA);
    free(flight->destinationIATA);
}
