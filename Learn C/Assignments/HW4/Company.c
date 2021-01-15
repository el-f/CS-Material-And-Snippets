#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "Company.h"
#include "General.h"
#include "fileHelper.h"
#include "macros.h"

static const char *sortOptStr[eNofSortOpt] = {
        "None", "Hour", "Date", "Airport takeoff code", "Airport landing code"};


int initCompanyFromFile(Company *pComp, AirportManager *pManaer, const char *fileName) {
    L_init(&pComp->flighDateList);
    if (loadCompanyFromFile(pComp, pManaer, fileName)) {
        initDateList(pComp);
        return 1;
    }
    return 0;
}

void initCompany(Company *pComp, AirportManager *pManaer) {
    printf("-----------  Init Airline Company\n");
    L_init(&pComp->flighDateList);

    pComp->name = getStrExactName("Enter company name");
    pComp->flightArr = NULL;
    pComp->flightCount = 0;
}

void initDateList(Company *pComp) {
    for (int i = 0; i < pComp->flightCount; i++) {
        if (isUniqueDate(pComp, i)) {
            char *sDate = createDateString(&pComp->flightArr[i]->date);
            L_insert(&(pComp->flighDateList.head), sDate);
        }
    }
}

int isUniqueDate(const Company *pComp, int index) {
    Date *pCheck = &pComp->flightArr[index]->date;
    for (int i = 0; i < index; i++) {
        if (equalDate(&pComp->flightArr[i]->date, pCheck))
            return 0;
    }
    return 1;
}

int addFlight(Company *pComp, const AirportManager *pManager) {

    if (pManager->count < 2) {
        printf("There are not enoght airport to set a flight\n");
        return 0;
    }
    pComp->flightArr = (Flight **) realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight *));
    if (!pComp->flightArr)
        return 0;
    pComp->flightArr[pComp->flightCount] = (Flight *) calloc(1, sizeof(Flight));
    if (!pComp->flightArr[pComp->flightCount])
        return 0;
    initFlight(pComp->flightArr[pComp->flightCount], pManager);
    if (isUniqueDate(pComp, pComp->flightCount)) {
        char *sDate = createDateString(&pComp->flightArr[pComp->flightCount]->date);
        L_insert(&(pComp->flighDateList.head), sDate);
    }
    pComp->flightCount++;
    return 1;
}

void printCompany(const Company *pComp, const char *str, ...) {
    va_list list;
    const char *strTemp;
    int first = 1;
    int combineLength = (int) strlen(pComp->name) + 1;
    char *longStr = calloc(1, combineLength);
    int len;
    strcpy(longStr, pComp->name);

    va_start(list, str);
    strTemp = str;
    while (strTemp != NULL) {
        len = (int) strlen(strTemp) + first;

        longStr = (char *) realloc(longStr, (combineLength + len + 1) * sizeof(char));
        if (!longStr) {
            printf("malloc error!\n");
            return;
        }

        if (first) {
            first = 0;
            strcat(longStr, "_");
            combineLength++;
        }

        strcat(longStr, strTemp);
        combineLength += len;

        strTemp = va_arg(list, const char*);
        if (strTemp != NULL) {
            longStr = (char *) realloc(longStr, (++combineLength * sizeof(char)));
            if (!longStr) {
                printf("malloc error!\n");
                return;
            }
            strcat(longStr, "_");
        }

    }
    va_end(list);

    printf("Company %s:\n", longStr);
    printf("Has %d flights\n", pComp->flightCount);
#ifdef DETAIL_PRINT
    generalArrayFunction((void *) pComp->flightArr, pComp->flightCount, sizeof(Flight **), printFlightV);
    printf("\nFlight Date List:");
    L_print(&pComp->flighDateList, printStr);
#endif
    free(longStr);
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
        printf("There are %d flights\n", count);
    else
        printf("There are No flights\n");

    printf("from %s to %s\n", codeOrigin, codeDestination);
}


#ifdef COMPRESSED_BINARY_FILE

int saveCompanyToFile(const Company *pComp, const char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "wb");
    CHECK_MSG_RETURN_0(fp, "Error open company file to write");

    BYTE data[2] = {0};
    data[0] = (BYTE) strlen(pComp->name);
    data[0] |= (BYTE) pComp->sortOpt << 4;
    data[0] |= (BYTE) pComp->flightCount << 7;
    data[1] = pComp->flightCount >> 1;

    if (fwrite(data, sizeof(BYTE), 2, fp) != 2) {
        MSG_CLOSE_RETURN_0(fp, "Error writing company metadata");
    }

    CHECK_RETURN_0(writeCharsToFile(pComp->name, (int) (strlen(pComp->name) + 1), fp, "Error writing company name!\n"));

    for (int i = 0; i < pComp->flightCount; i++) {
        CHECK_0_MSG_CLOSE_FILE(saveFlightToFile(pComp->flightArr[i], fp), fp, "Error write specific flight");
    }

    fclose(fp);
    return 1;
}

int loadCompanyFromFile(Company *pComp, const AirportManager *pManager, const char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "rb");
    CHECK_MSG_RETURN_0(fp, "Error open company file to write");

    BYTE data[2] = {0};
    if (fread(data, sizeof(BYTE), 2, fp) != 2) {
        MSG_CLOSE_RETURN_0(fp, "Error reading company metadata!");
    }

    int nameLen = data[0] & 0xf;
    pComp->name = readStringFromCompressedFile(
            fp,
            "Error reading Company Name!",
            nameLen + 1 /*for some reason there is useless extra byte in the given file*/
    );
    CHECK_RETURN_0(pComp->name);

    pComp->sortOpt = (data[0] >> 4) & 7;

    pComp->flightCount = (data[0] >> 7) & 1 | (data[1] << 1);

    if (pComp->flightCount > 0) {
        pComp->flightArr = malloc(pComp->flightCount * sizeof(Flight *));
        CHECK_NULL_MSG_CLOSE_FILE(pComp->flightArr, fp, "Malloc Error");
    } else {
        pComp->flightArr = NULL;
    }

    for (int i = 0; i < pComp->flightCount; ++i) {
        pComp->flightArr[i] = calloc(1, sizeof(Flight));
        CHECK_NULL_MSG_CLOSE_FILE(pComp->flightArr[i], fp, "Calloc Error");
        if (!loadFlightFromFile(pComp->flightArr[i], pManager, fp)) {
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

#else
int saveCompanyToFile(const Company *pComp, const char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "wb");

    CHECK_MSG_RETURN_0(fp, "Error open company file to write");

    if (!writeStringToFile(pComp->name, fp, "Error write comapny name\n"))
        return 0;

    if (!writeIntToFile(pComp->flightCount, fp, "Error write flight count\n"))
        return 0;

    if (!writeIntToFile((int) pComp->sortOpt, fp, "Error write sort option\n"))
        return 0;

    for (int i = 0; i < pComp->flightCount; i++) {
        if (!saveFlightToFile(pComp->flightArr[i], fp))
            return 0;
    }

    fclose(fp);
    return 1;
}

int loadCompanyFromFile(Company *pComp, const AirportManager *pManager, const char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "rb");

    CHECK_MSG_RETURN_0(fp, "Error open company file to write");

    pComp->flightArr = NULL;


    pComp->name = readStringFromFile(fp, "Error reading company name\n");
    if (!pComp->name)
        return 0;

    if (!readIntFromFile(&pComp->flightCount, fp, "Error reading flight count name\n"))
        return 0;

    int opt;
    if (!readIntFromFile(&opt, fp, "Error reading sort option\n"))
        return 0;

    pComp->sortOpt = (eSortOption) opt;

    if (pComp->flightCount > 0) {
        pComp->flightArr = (Flight **) malloc(pComp->flightCount * sizeof(Flight *));
        CHECK_NULL_MSG_CLOSE_FILE(pComp->flightArr, fp, "Allocation error");
    } else
        pComp->flightArr = NULL;

    for (int i = 0; i < pComp->flightCount; i++) {
        pComp->flightArr[i] = (Flight *) calloc(1, sizeof(Flight));
        if (!pComp->flightArr[i]) {
            printf("Allocation error\n");
            fclose(fp);
            return 0;
        }
        if (!loadFlightFromFile(pComp->flightArr[i], pManager, fp))
            return 0;
    }

    fclose(fp);
    return 1;
}
#endif


void sortFlight(Company *pComp) {
    pComp->sortOpt = showSortMenu();
    int (*compare)(const void *air1, const void *air2) = NULL;

    switch (pComp->sortOpt) {
        case eHour:
            compare = compareByHour;
            break;
        case eDate:
            compare = compareByDate;
            break;
        case eSorceCode:
            compare = compareByCodeOrig;
            break;
        case eDestCode:
            compare = compareByCodeDest;
            break;

    }

    if (compare != NULL)
        qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight *), compare);

}


void findFlight(const Company *pComp) {
    int (*compare)(const void *air1, const void *air2) = NULL;
    Flight f = {0};
    Flight *pFlight = &f;


    switch (pComp->sortOpt) {
        case eHour:
            f.hour = getFlightHour();
            compare = compareByHour;
            break;
        case eDate:
            getchar();
            getCorrectDate(&f.date);
            compare = compareByDate;
            break;
        case eSorceCode:
            getchar();
            getAirportCode(f.originCode);
            compare = compareByCodeOrig;
            break;
        case eDestCode:
            getchar();
            getAirportCode(f.destCode);
            compare = compareByCodeDest;
            break;
    }

    if (compare != NULL) {
        Flight **pF = bsearch(&pFlight, pComp->flightArr, pComp->flightCount, sizeof(Flight *), compare);
        if (pF == NULL)
            printf("Flight was not found\n");
        else {
            printf("Flight found, ");
            printFlight(*pF);
        }
    } else {
        printf("The search cannot be performed, array not sorted\n");
    }

}

eSortOption showSortMenu() {
    int opt;
    printf("Base on what field do you want to sort?\n");
    do {
        for (int i = 1; i < eNofSortOpt; i++)
            printf("Enter %d for %s\n", i, sortOptStr[i]);
        scanf("%d", &opt);
    } while (opt < 0 || opt > eNofSortOpt);

    return (eSortOption) opt;
}

void freeCompany(Company *pComp) {
    generalArrayFunction((void *) pComp->flightArr, pComp->flightCount, sizeof(Flight **), freeFlight);
    free(pComp->flightArr);
    free(pComp->name);
    L_free(&pComp->flighDateList, freePtr);
}
