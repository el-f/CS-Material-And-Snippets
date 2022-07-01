#ifndef __YELLOW_PAGES
#define __YELLOW_PAGES

#include <iostream>
using namespace std;

class YellowPages
{
public:
	static YellowPages* getInstance();
	~YellowPages();

private:
	YellowPages();

	YellowPages(const YellowPages& other);
	const YellowPages& operator=(const YellowPages& other);

	static YellowPages theYellowPages;
};

#endif // __YELLOW_PAGES
