#ifndef __GEOMETRIC_SERIES_H
#define __GEOMETRIC_SERIES_H

#include "series.h"

class GeometricSeries : public Series
{
public:
	GeometricSeries(int a1, int jump) : Series(a1, jump) {}

	virtual int getSum(int n) const override;
	virtual int getElement(int n) const override;
};

#endif // __GEOMETRIC_SERIES_H

