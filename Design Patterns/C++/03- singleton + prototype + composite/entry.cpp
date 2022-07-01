#include <iostream>
#include <string>
using namespace std;

#include "entry.h"

Entry::Entry(const string& name, const string& adddress, const string& phone)
{
	this->name = name;
	this->address = address;
	this->phone = phone;
}

void Entry::show() const
{
	cout << "\tName: " << name
		 << "\n\tAddress: " << address
		 << "\n\tPhone: " << phone << endl;
}

Component* Entry::clone() const
{
	return new Entry(*this);
}
