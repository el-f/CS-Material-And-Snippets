#include "arithmeticSeries.h"
#include "geometricSeries.h"

int main()
{
	Series* someSeries[4];

	someSeries[0] = new ArithmeticSeries(1, 2);
	someSeries[1] = new GeometricSeries(1, 2);
	someSeries[2] = new ArithmeticSeries(3, 4);
	someSeries[3] = new GeometricSeries(3, 4);

	for (int i = 0; i < 4 ; i++) {
		cout << *someSeries[i] << endl;
		for (int j = 2; j <= 5; j++) {
			cout << "\ta" << j << " = " << someSeries[i]->getElement(j);
			cout << ", s" << j << " = " << someSeries[i]->getSum(j) << endl;
		}
	}

	for (int i = 0; i < 4; i++)
		delete someSeries[i];
}