#ifndef __STREET_CAT_H
#define __STREET_CAT_H

#include "cat.h"

class StreetCat : virtual public Cat
{
protected:
	int numOfFights;
public:
	StreetCat(const Cat& base, int numOfFights);
	StreetCat(Cat&& base, int numOfFights);

	void setNumOfFights(int numOfFights) {this->numOfFights=numOfFights;}
	int  getNumOfFights() const {return numOfFights;}

	friend ostream& operator<<(ostream& os, const StreetCat& cat);
};

#endif // __STREET_CAT_H
