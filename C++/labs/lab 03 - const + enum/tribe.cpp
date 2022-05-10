#include <iostream>
using namespace std;

#include "tribe.h"

void Tribe::init(int max)
{
	maxSurvivors = max; 
	allSurvivors = new Survivor*[maxSurvivors];

	numOfSurvivors = 0;
}
bool Tribe::addSurvivor(const char* name, int age, Survivor::eStatus s)
{
	if (numOfSurvivors == maxSurvivors)
		return false;

	allSurvivors[numOfSurvivors] = new Survivor;
	allSurvivors[numOfSurvivors]->init(name, age, s);

	numOfSurvivors++;
	return true;
}

void Tribe::print() const
{
	for (int i = 0; i < numOfSurvivors; i++)
		allSurvivors[i]->print();
}

void Tribe::freeMemory()
{
	for (int i = 0; i < numOfSurvivors; i++)
		delete allSurvivors[i];

	delete[]allSurvivors;
}
