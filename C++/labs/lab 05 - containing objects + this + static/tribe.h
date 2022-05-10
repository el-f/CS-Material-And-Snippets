#ifndef __TRIBE_H
#define __TRIBE_H

#include "survivor.h"

class Tribe
{
private:
	Survivor** allSurvivors;
	int maxSurvivors;
	int numOfSurvivors;
	Bandana theTribesBandana;

public:
	Tribe(const Bandana& bandana, int max=5);
	Tribe(const Tribe& t) = delete;
	~Tribe();

	bool addSurvivor(const char* name, int age, Survivor::eStatus s);
	void print() const;
	bool hasMoreSpace() const { return numOfSurvivors < maxSurvivors; }

	const Bandana& getBandana() const { return theTribesBandana; }
};

#endif // __TRIBE_H
