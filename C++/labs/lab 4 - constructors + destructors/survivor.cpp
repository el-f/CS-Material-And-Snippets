#pragma warning (disable: 4996)

#include <iostream>
using namespace std;

#include "survivor.h"

const char* statusStr[] = { "Single", "Married", "In a relationship" };

Survivor::Survivor(const char* n, int a, eStatus s)
{
	setName(n);
	age = a;
	theStatus = s;
}

Survivor::~Survivor()
{
	delete[]name;
}

void Survivor::print() const
{
	cout << "Name: " << name << ", age: " << age 
		<< ", status: " << statusStr[(int)theStatus] << endl;
}

bool Survivor::setName(const char* n)
{
	delete[]name;
	name = new char[strlen(n) + 1];
	strcpy(name, n);

	return true;
}
