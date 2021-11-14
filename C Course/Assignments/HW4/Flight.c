#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"
#include "General.h"
#include "fileHelper.h"


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

void printFlight(const Flight *pFlight) {
    printf("Flight From %s To %s\t", pFlight->originCode, pFlight->destCode);
    printDate(&pFlight->date);
    printf("Hour: %d\n", pFlight->hour);
}

void printFlightV(void *val) {
    const Flight *pFlight = *(const Flight **) val;
    printFlight(pFlight);
}

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
        myGets(code, MAX_STR_LEN, stdin);
        port = findAirportByCode(pManager, code);
        if (port == NULL)
            printf("No airport in this country - try again\n");
    } while (port == NULL);

    return port;
}

int saveFlightToFile(const Flight *pF, FILE *fp) {
#ifdef COMPRESSED_BINARY_FILE

    if (fwrite(pF->originCode, sizeof(BYTE), 3, fp) != 3) { return 0; }
    if (fwrite(pF->destCode, sizeof(BYTE), 3, fp) != 3) { return 0; }

    int datetime = pF->hour;
    datetime |= (pF->date.day << 5);
    datetime |= pF->date.month << 10;
    datetime |= pF->date.year << 14;

    if (fwrite(&datetime, sizeof(int), 1, fp) != 1)
        return 0;

#else
    if (fwrite(pF, sizeof(Flight), 1, fp) != 1) {
        printf("Error write flight\n");
        return 0;
    }
#endif
    return 1;
}


int loadFlightFromFile(Flight *pF, const AirportManager *pManager, FILE *fp) {
#ifdef COMPRESSED_BINARY_FILE
    char origin[CODE_LENGTH + 1] = {0};
    char destination[CODE_LENGTH + 1] = {0};


    if (fread(&origin, sizeof(BYTE), 3, fp) != 3) {
        MSG_CLOSE_RETURN_0(fp, "Error reading origin IATA");
    }
    if (fread(&destination, sizeof(BYTE), 3, fp) != 3) {
        MSG_CLOSE_RETURN_0(fp, "Error reading destination IATA");
    }

    CHECK_NULL_MSG_CLOSE_FILE(findAirportByCode(pManager, origin), fp, "Unknown origin IATA");
    CHECK_NULL_MSG_CLOSE_FILE(findAirportByCode(pManager, destination), fp, "Unknown destination IATA");

    strcpy(pF->originCode, origin);
    strcpy(pF->destCode, destination);

    int datetime;
    if (fread(&datetime, sizeof(int), 1, fp) != 1) {
        MSG_CLOSE_RETURN_0(fp, "Error read datetime");
    }

    pF->hour = datetime & 0x1f;
    pF->date.day = (datetime >> 5) & 0x1f;
    pF->date.month = (datetime >> 10) & 0xf;
    pF->date.year = (datetime >> 14) & 0x3ffff;

#else
    if (fread(pF, sizeof(Flight), 1, fp) != 1) {
        printf("Error read flight\n");
        return 0;
    }
#endif
    return 1;
}

int compareByCodeOrig(const void *flight1, const void *flight2) {
    const Flight *pFlight1 = *(const Flight **) flight1;
    const Flight *pFlight2 = *(const Flight **) flight2;
    return strcmp(pFlight1->originCode, pFlight2->originCode);
}

int compareByCodeDest(const void *flight1, const void *flight2) {
    const Flight *pFlight1 = *(const Flight **) flight1;
    const Flight *pFlight2 = *(const Flight **) flight2;
    return strcmp(pFlight1->destCode, pFlight2->destCode);
}

int compareByHour(const void *flight1, const void *flight2) {
    const Flight *pFlight1 = *(const Flight **) flight1;
    const Flight *pFlight2 = *(const Flight **) flight2;
    return (pFlight1->hour - pFlight2->hour);
}

int compareByDate(const void *flight1, const void *flight2) {
    const Flight *pFlight1 = *(const Flight **) flight1;
    const Flight *pFlight2 = *(const Flight **) flight2;

    Date d1 = pFlight1->date;
    Date d2 = pFlight2->date;

    if (d1.year > d2.year)
        return 1;
    if (d1.year < d2.year)
        return -1;

    if (d1.month > d2.month)
        return 1;
    if (d1.month < d2.month)
        return -1;

    if (d1.day > d2.day)
        return 1;
    if (d1.day < d2.day)
        return -1;

    return 0;
}


void freeFlight(void *val) {
    Flight *pFlight = *(Flight **) val;
    free(pFlight);
}
