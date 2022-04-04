#include "siamiStreetCat.h"

SiamiStreetCat::SiamiStreetCat(const Cat& base, int numOfFights, const char* favoriteFood)
	: Cat(base), StreetCat(base, numOfFights), SiamiCat(base, favoriteFood)
{
}

SiamiStreetCat::SiamiStreetCat(Cat&& base, int numOfFights, const char* favoriteFood)
	: Cat(std::move(base)), StreetCat(std::move(base), numOfFights), SiamiCat(std::move(base), favoriteFood)
{
}

ostream& operator<<(ostream& os, const SiamiStreetCat& cat)
{
	os << (Cat&)cat << "\tFavoriteFood: " << cat.favoriteFood << "\tNumOfFights: " << cat.numOfFights;
	return os;
}