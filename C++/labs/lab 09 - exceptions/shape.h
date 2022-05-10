#ifndef __SHAPE_H
#define __SHAPE_H

#pragma warning(disable: 4996)

#include <iostream>
using namespace std;

class Shape
{
protected:
	float frameWidth;
	char *color;

public:
	Shape(float frameWidth, const char* color);
	Shape(const Shape& other);
	virtual ~Shape();

	const Shape& operator=(const Shape& other);
	friend ostream& operator<<(ostream& os, const Shape& shape);

	virtual void toOs(ostream& os) const = 0;

	virtual float getArea() const = 0;
	virtual float getPerimeter() const = 0;
};

#endif