#ifndef __SHAPE_EXCEPTIONS_H_
#define __SHAPE_EXCEPTIONS_H_

#include <iostream>
using namespace std;

class ShapeExceptions
{
public:
	virtual void show() const = 0;
};

class CircleException :public ShapeExceptions
{
private:
	float radius;
public:

	CircleException(float radius) :radius(radius) {}

	virtual void show() const override
	{
		cout << "the radius " << radius << " is not valid for a circle" << endl;
	}
};

class SquareException : public ShapeExceptions
{
private:
	float sideLength;
public:

	SquareException(float sideLength) :sideLength(sideLength) {}

	virtual void show() const override
	{
		cout << "the length " << sideLength << " is not valid for a square" << endl;
	}
};

#endif // !__SHAPE_EXCEPTIONS_H_
