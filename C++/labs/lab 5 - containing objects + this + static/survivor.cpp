#pragma warning (disable: 4996)

#include <iostream>
using namespace std;

#include "survivor.h"
#include "tribe.h"

const char* statusStr[] = { "Single", "Married", "In a relationship" };

int Survivor::numberGenerator = 0;

Survivor::Survivor(const char* name, int age, eStatus status, const Tribe& theTribe) : theTribe(&theTribe), theBandana(theTribe.getBandana())
{
	serialNumber = ++numberGenerator;
	setName(name);
	age = age;
	theStatus = status;
}

Survivor::~Survivor()
{
	delete[]name;
}

void Survivor::print() const
{
	cout << "Name: " << name << "(S/N: " << serialNumber << "), age: " << age 
		<< ", status: " << statusStr[(int)theStatus] << ", ";
	theBandana.print();
	cout << endl;
}

bool Survivor::setName(const char* name)
{
	delete[]this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);

	return true;
}
