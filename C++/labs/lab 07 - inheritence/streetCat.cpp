#include "streetCat.h"

StreetCat::StreetCat(const Cat& base, int numOfFights) : Cat(base), numOfFights(numOfFights)
{
}

StreetCat::StreetCat(Cat&& base, int numOfFights) : Cat(std::move(base)), numOfFights(numOfFights)
{

}

ostream& operator<<(ostream& os, const StreetCat& cat)
{
	os << (Cat&)cat << "\tNumOfFights: " << cat.numOfFights;
	return os;
}
