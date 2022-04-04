#include <iostream>
using  namespace std;

#include "siamiStreetCat.h"

void main()
{
	SiamiStreetCat ssc1(Cat("mitzi", "gingi", 3.5), 5, "mouse");
	cout << ssc1 << endl;

	SiamiStreetCat ssc2(ssc1);
	cout << ssc2 << endl;
}