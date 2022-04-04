#ifndef __SIAMI_CAT_H
#define __SIAMI_CAT_H

#include "cat.h"

class SiamiCat : virtual public Cat
{
protected:
	char* favoriteFood;
public:
	SiamiCat(const Cat& base, const char* favoriteFood);
	SiamiCat(Cat&& base, const char* favoriteFood);
	SiamiCat(const SiamiCat& other);
	SiamiCat(SiamiCat&& other);
	~SiamiCat();

	const SiamiCat& operator=(const SiamiCat& other);
	const SiamiCat& operator=(SiamiCat&& other);

	void        setFavoriteFood(const char* favoriteFood);
	const char* getFavoriteFood() const {return favoriteFood;}

	friend ostream& operator<<(ostream& os, const SiamiCat& cat);
};

#endif // __SIAMI_CAT_H
