#include "yellowPages.h"

YellowPages YellowPages::theYellowPages;

YellowPages::YellowPages() : mainCategory("main") 
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

void YellowPages::addCategory(const Category& c) 
{
	mainCategory.addComponent(*c.clone());
}

void YellowPages::show() const
{
	mainCategory.show();
}