#include "siamiCat.h"

SiamiCat::SiamiCat(const Cat& base, const char* favoriteFood) : Cat(base), favoriteFood(NULL)
{
	setFavoriteFood(favoriteFood);
}

SiamiCat::SiamiCat(Cat&& base, const char* favoriteFood) : Cat(std::move(base)), favoriteFood(NULL)
{
	setFavoriteFood(favoriteFood);
}

SiamiCat::SiamiCat(const SiamiCat& other) : Cat(other), favoriteFood(NULL)
{
	*this = other;
}

SiamiCat::SiamiCat(SiamiCat&& other) : Cat(std::move(other)), favoriteFood(NULL)
{
	*this = std::move(other);
}

SiamiCat::~SiamiCat()
{
	delete []favoriteFood;
}

const SiamiCat& SiamiCat::operator=(const SiamiCat& other) 
{
	if (this != &other)
	{
		Cat::operator =(other);
		setFavoriteFood(other.favoriteFood);
	}
	return *this;
}

const SiamiCat& SiamiCat::operator=(SiamiCat&& other)
{
	if (this != &other)
	{
		Cat::operator=(std::move(other));
		std::swap(favoriteFood, other.favoriteFood);
	}
	return *this;
}

void SiamiCat::setFavoriteFood(const char* favoriteFood)
{
	delete []this->favoriteFood;
	this->favoriteFood = strdup(favoriteFood);
}

ostream& operator<<(ostream& os, const SiamiCat& cat)
{
	os << (Cat&)cat << "\tFavoriteFood: " << cat.favoriteFood;
	return os;
}