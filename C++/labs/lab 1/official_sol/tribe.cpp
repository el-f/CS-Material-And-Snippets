#include <iostream>
using namespace std;

#include "tribe.h"

void initTribe(Tribe& theTribe) 
{
	cout << "How many survivors in tribe? ";
	cin >> theTribe.maxSurvivors;

	theTribe.allSurvivors = new Survivor*[theTribe.maxSurvivors];

	theTribe.numOfSurvivors = 0;
}
void readSurvivorsToTribe(Tribe& theTribe)
{
	char answer;
	do
	{
		cout << "Add another survivor to tribe? ";
		cin >> answer;

		if (answer == 'y')
		{
			theTribe.allSurvivors[theTribe.numOfSurvivors] = new Survivor;
			initSurvivor(*theTribe.allSurvivors[theTribe.numOfSurvivors]);

			theTribe.numOfSurvivors++;
		}
	} while (answer == 'y' && theTribe.numOfSurvivors < theTribe.maxSurvivors);
}

void printTribe(Tribe theTribe)
{
	for (int i = 0; i < theTribe.numOfSurvivors; i++)
		printSurvivor(*theTribe.allSurvivors[i]);
}

void deleteTribe(Tribe& theTribe)
{
	for (int i = 0; i < theTribe.numOfSurvivors; i++)
		delete theTribe.allSurvivors[i];

	delete[]theTribe.allSurvivors;
}
