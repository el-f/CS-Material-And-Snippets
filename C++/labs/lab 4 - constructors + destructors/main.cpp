#include <iostream>
using namespace std;

#include "survivor.h"
#include "tribe.h"

void readSurvivorsToTribe(Tribe& t);

int main()
{
	Tribe t1(5);

	cout << "Init tribe1:" << endl;
	t1.addSurvivor("gogo", 23, Survivor::eStatus::Married);
	t1.addSurvivor("momo", 24, Survivor::eStatus::Single);

	cout << "Init tribe2:" << endl;
	int max;
	cout << "Enter max survivors in tribe 2: ";
	cin >> max;
	Tribe t2(max);
	readSurvivorsToTribe(t2);
	
	cout << "\nThe survivors from tribe 1:\n";
	t1.print();

	cout << "\nThe survivors from tribe 2:\n";
	t2.print();
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
			char name[20];
			int age;

			cout << "Enter new survivor's name: ";
			cin >> name;

			cout << "Enter new survivor's age: ";
			cin >> age;

			int status;
			cout << "Enter status [0-Single, 1- Married, 2-In a relationship]: ";
			cin >> status;
			theTribe.addSurvivor(name, age, (Survivor::eStatus)status);
		}
	} while (answer == 'y' && theTribe.hasMoreSpace());
}