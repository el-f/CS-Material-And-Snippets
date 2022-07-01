#include "yellowPages.h"

YellowPages YellowPages::theYellowPages;

YellowPages::YellowPages()
{
	cout << "In YellowPages::YellowPages\n";
}

YellowPages::~YellowPages()
{
	cout << "In YellowPages::~YellowPages\n";
}

YellowPages* YellowPages::getInstance() 
{
	cout << "In YellowPages::getInstance\n";
	return &theYellowPages;
}
