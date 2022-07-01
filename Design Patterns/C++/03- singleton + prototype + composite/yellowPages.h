#ifndef __YELLOW_PAGES_H
#define __YELLOW_PAGES_H

#include <iostream>
using namespace std;

#include "category.h"

class YellowPages
{	
public:
	static YellowPages* getInstance(); // for SINGLETONE
	~YellowPages();

	void show() const;
	void addCategory(const Category& c);

private:
	YellowPages();  // for SINGLETONE

	YellowPages(const YellowPages& other);  
	const YellowPages& operator=(const YellowPages& other);

	static YellowPages theYellowPages;  // for SINGLETONE
	Category mainCategory;
};

#endif // __YELLOW_PAGES_H