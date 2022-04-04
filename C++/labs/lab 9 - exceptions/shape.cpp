#include "shape.h"

Shape::Shape(float frameWidth, const char* color)
{
	this->frameWidth = frameWidth;
	this->color = strdup(color);
}

Shape::Shape(const Shape& other) : color(NULL)
{
	*this = other;
}

Shape::~Shape()
{
	delete[] this->color;
}

const Shape& Shape::operator=(const Shape& other)
{
	if (this != &other)
	{
		this->frameWidth = other.frameWidth;
		delete[]this->color;
		this->color = strdup(other.color);
	}

	return *this;
}

ostream& operator<<(ostream& os, const Shape& shape) {
	os << typeid(shape).name() + 6 << " --> \tFrame width: " << shape.frameWidth << ", Color: " << shape.color << ", Area: " << shape.getArea() << ", Perimeter: " << shape.getPerimeter();
	shape.toOs(os);
	return os;
}