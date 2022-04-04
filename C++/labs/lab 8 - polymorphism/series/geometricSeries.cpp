#include "geometricSeries.h"
#include <math.h>

int GeometricSeries::getSum(int n) const
{
	return (a1 * (int)(pow(jump, n) - 1)) / (jump - 1);
}
int GeometricSeries::getElement(int n) const
{
	return (int)(a1 * pow(jump, n - 1));
}