#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"

const char *printableSortOptions[eNofSortOptions] = {
        "Not Sorted",
        "Sorted By Hour",
        "Sorted By Date",
        "Sorted By Origin Airport",
        "Sorted By Destination Airport"
};

void initCompany(Company *pComp) {
    printf("-----------  Init Airline Company\n");
    pComp->name = getStrExactName("Enter company name");
    pComp->flightArr = NULL;
    pComp->flightCount = 0;
    L_init(&pComp->flightDates);
    pComp->currentSort = unsorted;
}

int addFlight(Company *pComp, const AirportManager *pManager) {
    if (pManager->count < 2) {
        printf("There are not enough airports to set a flight\n");
        return 0;
    }
    pComp->flightArr = (Flight **) realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight *));
    if (!pComp->flightArr)
        return 0;
    pComp->flightArr[pComp->flightCount] = (Flight *) calloc(1, sizeof(Flight));
    if (!pComp->flightArr[pComp->flightCount])
        return 0;
    initFlight(pComp->flightArr[pComp->flightCount], pManager);
    if (!addDateToList(pComp, &pComp->flightArr[pComp->flightCount]->date)) return 0;

    pComp->flightCount++;
    pComp->currentSort = unsorted;
    return 1;
}

int addDateToList(Company *pComp, Date *date) {
    char *dateString = dateAsString(date);
    if (!dateString) return 0; // fail only on malloc fail
    if (L_find(pComp->flightDates.head.next, dateString, compareDateStrings) == NULL) {
        NODE *pNode = &pComp->flightDates.head;

        while (pNode->next != NULL && compareDateStrings(dateString, pNode->next->key) > 0) {
            pNode = pNode->next;
        }

        L_insert(pNode, dateString);
        return 1;
    }
    return 1; // flight with this date already exists
}

void printCompany(const Company *pComp) {
    printf("Company %s:\n", pComp->name);
    printf("Has %d flights\n", pComp->flightCount);
    if (pComp->flightCount == 0) return;

    printf("%s:\n", printableSortOptions[pComp->currentSort]);
    generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight *), printFlight);
    printf("All Flight Dates:\n");
    L_print(&pComp->flightDates, printDateString);
}

void printFlightsCount(const Company *pComp) {
    char codeOrigin[CODE_LENGTH + 1];
    char codeDestination[CODE_LENGTH + 1];

    if (pComp->flightCount == 0) {
        printf("No flight to search\n");
        return;
    }

    printf("Origin Airport\n");
    getAirportCode(codeOrigin);
    printf("Destination Airport\n");
    getAirportCode(codeDestination);

    int count = countFlightsInRoute(pComp->flightArr, pComp->flightCount, codeOrigin, codeDestination);
    if (count != 0)
        printf("There are %d flights ", count);
    else
        printf("There are No flights ");

    printf("from %s to %s\n", codeOrigin, codeDestination);
}

void freeCompany(Company *pComp) {
    generalArrayFunction(pComp->flightArr, pComp->flightCount, sizeof(Flight *), freeFlight);
    free(pComp->flightArr);
    free(pComp->name);
    L_free(&pComp->flightDates, free);
}

int (*chooseCompareFunction(Company *pComp))(const void *, const void *) {
    int choice;
    printf("Please choose from the following sort options:\n");
    for (int i = 1; i < eNofSortOptions; i++)
        printf("%d - %s\n", i, printableSortOptions[i]);
    scanf("%d", &choice);

    //clean buffer
    char tav;
    scanf("%c", &tav);

    int (*compareFunction)(const void *, const void *);

    switch (choice) {
        case sortedByHour:
            compareFunction = compareFlightsByHour;
            break;

        case sortedByDate:
            compareFunction = compareFlightsByDate;
            break;

        case sortedByOriginAirport:
            compareFunction = compareFlightsByOriginAirport;
            break;

        case sortedByDestinationAirport:
            compareFunction = compareFlightsByDestinationAirport;
            break;

        default:
            printf("Invalid Choice!\n");
            return NULL;
    }
    pComp->currentSort = choice;
    return compareFunction;
}

void sortFlights(Company *pComp) {
    if (pComp->flightCount == 0) {
        printf("Empty Flights list, nothing to sort...\n");
        return;
    }
    int (*compareFunction)(const void *, const void *) = chooseCompareFunction(pComp);
    if (compareFunction == NULL) return;

    qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight *), compareFunction);
}

void searchFlight(Company *pComp) {
    if (pComp->flightCount == 0) {
        printf("Empty Flights list, nothing to search...\n");
        return;
    }

    int (*compareFunction)(const void *, const void *);
    Flight key;

    switch (pComp->currentSort) {
        case unsorted:
            printf("Flights array is not sorted, cannot search...\n");
            return;

        case sortedByHour:
            compareFunction = compareFlightsByHour;
            key.hour = getFlightHour();
            break;

        case sortedByDate:
            compareFunction = compareFlightsByDate;
            getCorrectDate(&key.date);
            break;

        case sortedByOriginAirport:
            compareFunction = compareFlightsByOriginAirport;
            getAirportCode(key.originCode);
            break;

        case sortedByDestinationAirport:
            compareFunction = compareFlightsByDestinationAirport;
            getAirportCode(key.destCode);
            break;

        default:
            printf("Invalid current sort status!\n");
            return;
    }

    Flight *keyPtr = &key;
    Flight **foundFlight = bsearch(
            &keyPtr,
            pComp->flightArr,
            pComp->flightCount,
            sizeof(Flight *),
            compareFunction
    );

    if (foundFlight) {
        printFlight(foundFlight);
    } else {
        printf("Did not found any flight with these search parameters...\n");
    }
    printf("\n");
}

int writeCompanyToBinFile(FILE *fp, const Company *pComp) {
    int nameLength = (int) strlen(pComp->name) + 1;

    if (fwrite(&nameLength, sizeof(int), 1, fp) != 1) { return 0; }
    if (fwrite(pComp->name, sizeof(char), nameLength, fp) != nameLength) { return 0; }
    if (fwrite(&pComp->flightCount, sizeof(int), 1, fp) != 1) { return 0; };
    if (fwrite(&pComp->currentSort, sizeof(int), 1, fp) != 1) { return 0; };

    for (int i = 0; i < pComp->flightCount; i++) {
        if (!writeFlightToBinFile(fp, pComp->flightArr[i])) { return 0; }
    }
    return 1;
}

int readCompanyFromBinFile(FILE *fp, Company *pComp) {
    L_init(&pComp->flightDates);
    pComp->flightArr = NULL;

    int nameLength;
    if (!fread(&nameLength, sizeof(int), 1, fp)) { return 0; }
    pComp->name = malloc(sizeof(char) * nameLength);
    if (!pComp->name) {
        printf("Failed Malloc!\n");
        return 0;
    }

    if (fread(pComp->name, sizeof(char), nameLength, fp) != nameLength) { return 0; }
    if (fread(&pComp->flightCount, sizeof(int), 1, fp) != 1) { return 0; }
    if (fread(&pComp->currentSort, sizeof(int), 1, fp) != 1) { return 0; }
    if (pComp->currentSort < 0 || pComp->currentSort >= eNofSortOptions) { return 0; }

    for (int i = 0; i < pComp->flightCount; i++) {
        Flight *pFlight = malloc(sizeof(Flight));
        if (!readFlightFromBinFile(fp, pFlight)) {
            printf("Error reading flight #%d\n", i);
            return 0;
        }

        pComp->flightArr = (Flight **) realloc(pComp->flightArr, (i + 1) * sizeof(Flight *));
        if (!pComp->flightArr) { return 0; }

        pComp->flightArr[i] = pFlight;
        if (!addDateToList(pComp, &pFlight->date)) { return 0; }
    }
    return 1;
}

void generalArrayFunction(void *array, int arraySize, int elementSize, void (*function)(void *)) {
    for (int i = 0; i < arraySize; i++) {
        function((char *) array + i * elementSize);
    }
}