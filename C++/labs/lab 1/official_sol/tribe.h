#ifndef __TRIBE_H
#define __TRIBE_H

#include "survivor.h"

typedef struct
{
	Survivor** allSurvivors;
	int maxSurvivors;
	int numOfSurvivors;
} Tribe;

void initTribe(Tribe& theTribe);
void readSurvivorsToTribe(Tribe& theTribe);
void printTribe(Tribe theTribe);
void deleteTribe(Tribe& theTribe);

#endif // __TRIBE_H
