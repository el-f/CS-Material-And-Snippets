#include "square.h"

Square::Square(float frameWidth, const char *color, float sideLength) throw(SquareException)
	: Shape(frameWidth, color)
{
	if (sideLength < 0)
		throw SquareException(sideLength);
	this->sideLength = sideLength;
}

float Square::getArea() const
{
	return this->sideLength * this->sideLength;
}

float Square::getPerimeter() const
{
	return this->sideLength * 4;
}

void Square::draw() const {
	for (int i = 0; i < this->sideLength; i++)
	{
		for (int j = 0; j < this->sideLength; j++)
		{
			cout << "*";
		}

		cout << endl;
	}
}

void Square::toOs(ostream& os) const
{
	os << ", Side Length: " << sideLength;
}