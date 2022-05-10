#pragma warning(disable: 4996)

#include "shape.h"

Shape::Shape(const char* color, int width)
{
	this->color = new char[strlen(color)+1];
	strcpy(this->color, color);

	this->width = width;
}

Shape::Shape(const Shape& other) : color(NULL)
{
	*this = other;
}

Shape::Shape(Shape&& other)
{
	color = other.color;
	other.color = nullptr;

	width = other.width;
}

Shape::~Shape()
{
	delete[]color;
}

const Shape& Shape::operator=(const Shape& other)
{
	if (this != &other)
	{
		delete[]color;
		color = new char[strlen(other.color) + 1];
		strcpy(this->color, other.color);

		width = other.width;
	}
	return *this;
}
const Shape& Shape::operator=(Shape&& other)
{
	if (this != &other)
	{
		std::swap(color, other.color);
		width = other.width;
	}
	return *this;
}

ostream& operator<<(ostream& os, const Shape& s)
{
	os << typeid(s).name() + 6 << " details: color=" << s.color << ", width=" << s.width;
	s.toOs(os);
	return os;
}