#ifndef __SERIES_H
#define __SERIES_H

#include <iostream>
using namespace std;

class Series
{
protected:
	int a1;
	int jump;

public: 
	Series(int a1, int jump) : a1(a1), jump(jump) {}
	virtual ~Series() {}

	virtual int getSum(int n) const = 0;
	virtual int getElement(int n) const = 0;
	
	friend ostream& operator<<(ostream& os, const Series& s);
};

#endif // __SERIES_H
