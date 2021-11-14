#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"


void initFlight(Flight *pFlight, const AirportManager *pManager) {
    Airport *pPortOr = setAirportToFlight(pManager, "Enter code of origin airport:");
    strcpy(pFlight->originCode, pPortOr->code);
    int same;
    Airport *pPortDes;
    do {
        pPortDes = setAirportToFlight(pManager, "Enter code of destination airport:");
        same = isSameAirport(pPortOr, pPortDes);
        if (same)
            printf("Same origin and destination airport\n");
    } while (same);
    strcpy(pFlight->destCode, pPortDes->code);
    getCorrectDate(&pFlight->date);
    pFlight->hour = getFlightHour();
}

int isFlightInRoute(const Flight *pFlight, const char *codeSource, const char *codeDest) {
    if ((strcmp(pFlight->originCode, codeSource) == 0) &&
        (strcmp(pFlight->destCode, codeDest) == 0))
        return 1;

    return 0;
}

int countFlightsInRoute(Flight **arr, int size, const char *codeSource,
                        const char *codeDest) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (isFlightInRoute(arr[i], codeSource, codeDest))
            count++;
    }
    return count;
}

void printFlight(void *pFlight) {
    const Flight **pf = (const Flight **) pFlight;
    printf("Flight From %s To %s\t", (*pf)->originCode, (*pf)->destCode);
    printDate(&(*pf)->date);
    printf("Hour: %d\n", (*pf)->hour);
}


int getFlightHour() {
    int h;
    do {
        printf("Enter flight hour [0-23]:\t");
        scanf("%d", &h);
    } while (h < 0 || h > 23);
    return h;
}

Airport *setAirportToFlight(const AirportManager *pManager, const char *msg) {
    char code[MAX_STR_LEN];
    Airport *port;
    do {
        printf("%s\t", msg);
        myGets(code, MAX_STR_LEN);
        port = findAirportByCode(pManager, code);
        if (port == NULL)
            printf("No airport in this country - try again\n");
    } while (port == NULL);

    return port;

}

void freeFlight(void *pFlight) {
    Flight **pf = (Flight **) pFlight;
    free(*pf);
}

int compareFlightsByHour(const void *flightP1, const void *flightP2) {
    return (*(const Flight **) flightP1)->hour - (*(const Flight **) flightP2)->hour;
}

int compareFlightsByDate(const void *flightP1, const void *flightP2) {
    return compareDates(&(*(const Flight **) flightP1)->date, &(*(const Flight **) flightP2)->date);
}

int compareFlightsByOriginAirport(const void *flightP1, const void *flightP2) {
    return strcmp((*(const Flight **) flightP1)->originCode, (*(const Flight **) flightP2)->originCode);
}

int compareFlightsByDestinationAirport(const void *flightP1, const void *flightP2) {
    return strcmp((*(const Flight **) flightP1)->destCode, (*(const Flight **) flightP2)->destCode);
}

int writeFlightToBinFile(FILE *fp, const Flight *flight) {
    if (fwrite(flight->originCode, sizeof(char), CODE_LENGTH + 1, fp) != CODE_LENGTH + 1) {
        return 0;
    }
    if (fwrite(flight->destCode, sizeof(char), CODE_LENGTH + 1, fp) != CODE_LENGTH + 1) {
        return 0;
    }
    if (fwrite(&flight->hour, sizeof(int), 1, fp) != 1) {
        return 0;
    }
    if (!writeDateToBinaryFile(fp, &flight->date)) {
        return 0;
    }

    return 1;
}

int readFlightFromBinFile(FILE *fp, Flight *flight) {
    if (fread(flight->originCode, sizeof(char), CODE_LENGTH + 1, fp) != CODE_LENGTH + 1) {
        return 0;
    }
    if (fread(flight->destCode, sizeof(char), CODE_LENGTH + 1, fp) != CODE_LENGTH + 1) {
        return 0;
    }
    if (!fread(&flight->hour, sizeof(int), 1, fp)) {
        return 0;
    }
    if (!readDateFromBinaryFile(fp, &flight->date)) {
        return 0;
    }

    return 1;
}
