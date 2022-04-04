#ifndef __SQUARE_H
#define __SQUARE_H

#pragma warning(disable: 4996)

#include <iostream>
using namespace std;

#include "shape.h"
#include "ShapeException.h"


class Square : public Shape
{
protected:
	float sideLength;

public:
	Square(float frameWidth, const char* color, float sideLength) throw(SquareException);

	virtual void toOs(ostream& os) const override;

	void draw() const;

	virtual float getArea() const override;
	virtual float getPerimeter() const override;
};

#endif