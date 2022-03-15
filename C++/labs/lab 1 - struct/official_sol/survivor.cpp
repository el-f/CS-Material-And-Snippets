#include <iostream>
using namespace std;

#include "survivor.h"

void initSurvivor(Survivor& s)
{
	cout << "Enter survivor's name: ";
	cin >> s.name;

	cout << "Enter survivor's age: ";
	cin >> s.age;
}

void printSurvivor(Survivor s)
{
	cout << "Name: " << s.name << ", age: " << s.age << endl;
}
