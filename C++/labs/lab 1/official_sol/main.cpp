#include <iostream>
using namespace std;

#include "survivor.h"
#include "tribe.h"

int main()
{
	Tribe t1, t2;

	cout << "Init tribe1:" << endl;
	initTribe(t1);

	cout << "Init tribe2:" << endl;
	initTribe(t2);

	cout << "Enter survivors to tribe 1:" << endl;
	readSurvivorsToTribe(t1);

	cout << "Enter survivors to tribe 2:" << endl;
	readSurvivorsToTribe(t2);
	
	cout << "\nThe survivors from tribe 1:\n";
	printTribe(t1);

	cout << "\nThe survivors from tribe 2:\n";
	printTribe(t2);

	deleteTribe(t1);
	deleteTribe(t2);
}