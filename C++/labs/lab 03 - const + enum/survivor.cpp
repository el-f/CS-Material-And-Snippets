#pragma warning (disable: 4996)

#include <iostream>
using namespace std;

#include "survivor.h"

const char* statusStr[] = { "Single", "Married", "In a relationship" };

void Survivor::init(const char* n, int a, eStatus s)
{
	strcpy(name, n);
	age = a;
	theStatus = s;
}

void Survivor::print() const
{
	cout << "Name: " << name << ", age: " << age 
		<< ", status: " << statusStr[(int)theStatus] << endl;
}
