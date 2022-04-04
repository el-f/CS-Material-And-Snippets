#pragma warning(disable: 4996)

#include <string>
#include <iostream>
using namespace std;

#include "bandana.h"

Bandana::Bandana(const char* color, int length)
{
	strcpy(this->color, color);
	this->length = length;
}

void Bandana::print() const
{
	cout << "Bandana's color is " << color << ", " << length << "cm.";
}