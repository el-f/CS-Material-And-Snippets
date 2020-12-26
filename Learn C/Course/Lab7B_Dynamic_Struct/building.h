#ifndef BUILDING
#define BUILDING

#include "family.h"

typedef struct {
    Family **allFamilies;
    int maxFamilies;
    int numOfFamilies;
} Building;


int initBuilding(Building *pBuilding);

void printBuilding(const Building *pBuilding);

void freeBuilding(Building *pBuilding);


#endif //LAB7_BUILDING_H
