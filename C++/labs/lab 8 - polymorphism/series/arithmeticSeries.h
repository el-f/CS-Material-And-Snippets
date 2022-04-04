#ifndef __ARITHMETIC_SERIES_H
#define __ARITHMETIC_SERIES_H

#include "series.h"

class ArithmeticSeries : public Series
{
public:
	ArithmeticSeries(int a1, int jump) : Series(a1, jump) {}

	virtual int getSum(int n) const override;
	virtual int getElement(int n) const override;
};

#endif // __ARITHMETIC_SERIES_H
