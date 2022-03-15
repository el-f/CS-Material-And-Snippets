#pragma warning (disable: 4996)

#include <iostream>
using namespace std;

#include "survivor.h"

void Survivor::init(const char* n, int a)
{
	strcpy(name, n);
	age = a;
}

void Survivor::print()
{
	cout << "Name: " << name << ", age: " << age << endl;
}
