#ifndef __SHAPE_H
#define __SHAPE_H

#include <iostream>
using namespace std;
class Shape
{
protected:
	char* color;
	int width;

public:
	static constexpr double PI = 3.14;

	Shape(const char* color, int width);
	Shape(const Shape& other);
	Shape(Shape&& other);
	virtual ~Shape();

	const Shape& operator=(const Shape& other);
	const Shape& operator=(Shape&& other);

	virtual double getPerimeter() const = 0;
	virtual double getArea() const = 0;

	virtual void toOs(ostream& os) const = 0;

	friend ostream& operator<<(ostream& os, const Shape& s);
};

#endif // __SHAPE_H