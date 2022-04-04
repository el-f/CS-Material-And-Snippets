#ifndef __SIAMI_STREET_CAT_H
#define __SIAMI_STREET_CAT_H

#include <iostream>
using namespace std;

#include "siamiCat.h"
#include "streetCat.h"

class SiamiStreetCat : public StreetCat, public SiamiCat
{
public:
	SiamiStreetCat(const Cat& base, int numOfFights, const char* favoriteFood);
	SiamiStreetCat(Cat&& base, int numOfFights, const char* favoriteFood);

	friend ostream& operator<<(ostream& os, const SiamiStreetCat& cat);
};

#endif // __SIAMI_STREET_CAT_H