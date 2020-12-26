//
// Created by Elazar on 30/11/2020.
//

#include <stdio.h>
#include "building.h"
#include "funcs7B.h"

#define NEIGHBORHOOD_MAX_SIZE 5

int main() {

    Building neighborhood[NEIGHBORHOOD_MAX_SIZE];

    printf("Please enter number of buildings to init:\n");
    int numBuildings = scanInt();

    for (int i = 0; i < numBuildings; i++) {
        printf("Init Building %d:\n", i + 1);
        initBuilding(&neighborhood[i]);
    }
    printf("\nNeighborhood has %d buildings out of %d\n", numBuildings, NEIGHBORHOOD_MAX_SIZE);
    for (int i = 0; i < numBuildings; i++) {
        printf("\nBuilding %d ", i + 1);
        printBuilding(&neighborhood[i]);
    }
    for (int i = 0; i < numBuildings; i++) {
        freeBuilding(&neighborhood[i]);
    }


//    Family family;
//    Family family2;
//    initFamily(&family);
//    initFamily(&family2);
//
//    printFamily(&family);
//    printFamily(&family2);
//
//    freeFamily(&family);
//    freeFamily(&family2);

//    Building building;
//    initBuilding(&building);
//    printBuilding(&building);
//    freeBuilding(&building);
}