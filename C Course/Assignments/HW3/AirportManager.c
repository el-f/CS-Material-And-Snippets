#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "AirportManager.h"

int initManager(AirportManager *pManager) {
    printf("-----------  Init airport Manager\n");
    pManager->count = 0;
    L_init(&pManager->list);

    int count = 0;
    do {
        printf("How many airport?\t");
        scanf("%d", &count);
    } while (count < 0);

    //clean buffer
    char tav;
    scanf("%c", &tav);
    if (count == 0) return 1;


    for (int i = 0; i < count; i++) {
        addAirport(pManager);
    }

    return 1;
}

void insertAirportToList(AirportManager *pManager, Airport *airport) {
    NODE *pNode = &pManager->list.head;

    while (pNode->next != NULL && compareAirportsByCode(airport, pNode->next->key) > 0) {
        pNode = pNode->next;
    }

    L_insert(pNode, airport);
}

int addAirport(AirportManager *pManager) {
    Airport *airport = malloc(sizeof(Airport));
    if (!airport) return 0;

    setAirport(airport, pManager);
    insertAirportToList(pManager, airport);
    pManager->count++;
    return 1;
}

void setAirport(Airport *pPort, AirportManager *pManager) {
    while (1) {
        getAirportCode(pPort->code);
        if (checkUniqueCode(pPort->code, pManager))
            break;

        printf("This code already in use - enter a different code\n");
    }

    initAirportNoCode(pPort);
}

Airport *findAirportByCode(const AirportManager *pManager, const char *code) {
    Airport code_container;
    for (int i = 0; i < CODE_LENGTH + 1; i++) {
        code_container.code[i] = code[i];
    }
    NODE *result = L_find(pManager->list.head.next, &code_container, compareAirportsByCode);
    if (result != NULL) return result->key;
    return NULL;
}

int checkUniqueCode(const char *code, const AirportManager *pManager) {
    Airport *port = findAirportByCode(pManager, code);

    if (port != NULL)
        return 0;

    return 1;
}

void printAirports(const AirportManager *pManager) {
    printf("there are %d airports\n", pManager->count);
    L_print(&pManager->list, printAirport);
}

void freeManager(AirportManager *pManager) {
    L_free(&pManager->list, freeAirport);
}

void writeAirportManagerToTextFile(FILE *fp, const AirportManager *pManager) {
    fprintf(fp, "%d\n", pManager->count);

    NODE *pNode = pManager->list.head.next;

    while (pNode != NULL) {
        writeAirportToTextFile(fp, pNode->key);
        pNode = pNode->next;
    }
}

int readAirportManagerFromTextFile(FILE *fp, AirportManager *pManager) {
    if (fscanf(fp, "%d", &pManager->count) != 1) {
        printf("Error reading number of airports!\n");
        return 0;
    }
    L_init(&pManager->list);

    for (int i = 0; i < pManager->count; i++) {
        Airport *airport = malloc(sizeof(Airport));
        if (!airport) {
            printf("Malloc Failed!\n");
            return 0;
        }
        if (!readAirportFromTextFile(fp, airport)) {
            printf("Error reading airport #%d\n", i);
            return 0;
        }
        insertAirportToList(pManager, airport);
    }
    return 1;
}
