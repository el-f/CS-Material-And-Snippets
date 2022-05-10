#include "circle.h"

Circle::Circle(float frameWidth, const char* color, float radius)
	: Shape(frameWidth, color) 
{
	if (radius < 0)
		throw CircleException(radius);
		
	this->radius = radius;
}

void Circle::toOs(ostream& os) const
{
	os << ", Radius: " << radius;
}

float Circle::getArea() const
{
	return this->radius * this->radius * PI;
}

float Circle::getPerimeter() const
{
	return 2 * this->radius * PI;
}