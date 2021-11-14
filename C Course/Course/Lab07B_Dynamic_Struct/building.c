//
// Created by Elazar on 01/12/2020.
//

#include <stdio.h>
#include <malloc.h>
#include "building.h"
#include "funcs7B.h"

int initBuilding(Building *pBuilding) {
    printf("Enter max num of families:\n");
    pBuilding->maxFamilies = scanInt();

    pBuilding->allFamilies = (Family **) malloc(pBuilding->maxFamilies * sizeof(Family *));
    if (pBuilding->allFamilies == NULL) return 0;

    while (pBuilding->numOfFamilies < pBuilding->maxFamilies) {
        printf("Do you want to enter a family? y/n\n");
        if (!scanBool()) break;
        getchar(); //clear buffer

        Family *pFamily = (Family *) malloc(sizeof(Family));
        if (!pFamily) return 0; //family malloc failed
        if (!initFamily(pFamily)) return 0; //family name malloc failed

        pBuilding->allFamilies[pBuilding->numOfFamilies] = pFamily;
        pBuilding->numOfFamilies++;
    }

    return 1;
}

void printBuilding(const Building *pBuilding) {
    printf("Has %d families out of %d:\n", pBuilding->numOfFamilies, pBuilding->maxFamilies);
    for (int i = 0; i < pBuilding->numOfFamilies; i++) {
        printFamily(pBuilding->allFamilies[i]);
    }
}

void freeBuilding(Building *pBuilding) {
    for (int i = 0; i < pBuilding->numOfFamilies; i++) {
        freeFamily(pBuilding->allFamilies[i]);
        free(pBuilding->allFamilies[i]);
    }
    free(pBuilding->allFamilies);
}