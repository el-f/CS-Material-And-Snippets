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
	Tribe(int max=5);
	Tribe(const Tribe& t) = delete;
	~Tribe();

	bool addSurvivor(const char* name, int age, Survivor::eStatus s);
	void print() const;
	bool hasMoreSpace() const { return numOfSurvivors < maxSurvivors; }
};

#endif // __TRIBE_H
