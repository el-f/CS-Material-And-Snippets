#include "arithmeticSeries.h"

int ArithmeticSeries::getElement(int n) const
{
	return a1 + (n - 1) * jump;
}

int ArithmeticSeries::getSum(int n) const
{
	return n * (a1 + getElement(n)) / 2;
}