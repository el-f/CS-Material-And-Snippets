#ifndef __TRIBE_H
#define __TRIBE_H

#include "survivor.h"

class Tribe
{
private:
	Survivor** allSurvivors;
	int maxSurvivors;
	int numOfSurvivors;

public:
	void init(int max);
	bool addSurvivor(const char* name, int age);
	void print();
	void freeMemory();
	bool hasMoreSpace() { return numOfSurvivors < maxSurvivors; }
};

#endif // __TRIBE_H
