#ifndef __CIRCLE_H
#define __CIRCLE_H

#include "shape.h"

class Circle : public Shape
{
private:
	int radius;

public:
	Circle(const char* color, int width, int radius) : Shape(color, width) 
	{
		this->radius = radius;
	}

	virtual double getPerimeter() const override 
	{
		return 2 * PI * radius;
	}

	virtual double getArea() const override 
	{
		return PI * radius * radius;
	}

	virtual void toOs(ostream& os) const override  
	{
		os << ", radius=" << radius;
	}
};
#endif // __CIRCLE_H