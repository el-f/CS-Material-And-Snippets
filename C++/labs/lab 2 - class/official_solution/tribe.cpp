#include <iostream>
using namespace std;

#include "tribe.h"

void Tribe::init(int max)
{
	/*cout << "How many survivors in tribe? ";
	cin >> theTribe.maxSurvivors;
	*/
	
	maxSurvivors = max; 
	allSurvivors = new Survivor*[maxSurvivors];

	numOfSurvivors = 0;
}
bool Tribe::addSurvivor(const char* name, int age)
{
	if (numOfSurvivors == maxSurvivors)
		return false;

	allSurvivors[numOfSurvivors] = new Survivor;
	allSurvivors[numOfSurvivors]->init(name, age);

	numOfSurvivors++;
	return true;
}

void Tribe::print()
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
