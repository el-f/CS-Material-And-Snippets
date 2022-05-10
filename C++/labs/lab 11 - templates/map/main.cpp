#include <iostream>
using namespace std;

#include "map.h"

void main()
{
	Map<int, const char*> int2string;
	try
	{
		int2string[111] = "gogo";
		int2string[222] = "momo";
		int2string[333] = "yoyo";
	}
	catch (const char* msg)
	{
		cout << "In catch1: " << msg;
	}
	cout << int2string;

	try
	{
		int2string[222] = "mama";
		int2string[444] = "koko";
	}
	catch (const char* msg)
	{
		cout << "In catch2: " << msg;
	}
	cout << endl << int2string;

	cout << "-----------------------------------\n\n";
	Map<const char*, double> employeeToSalary;
	employeeToSalary["gogo"] = 1000;
	employeeToSalary["momo"] = 2000;
	employeeToSalary["yoyo"] = 3000;
	cout << employeeToSalary << endl;
}

/*
111 --> gogo
222 --> momo
333 --> yoyo
In catch2: Map is full
111 --> gogo
222 --> mama
333 --> yoyo
-----------------------------------

gogo --> 1000
momo --> 2000
yoyo --> 3000

Press any key to continue . . .
*/