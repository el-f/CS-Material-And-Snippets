#include <iostream>
using namespace std;

#include "yellowPages.h"

void main()
{
	cout << "Enter main\n";
	
	YellowPages* yp1 = YellowPages::getInstance();
	YellowPages* yp2 = YellowPages::getInstance();
	YellowPages* yp3 = YellowPages::getInstance();

	cout << "Exit main\n";
}

