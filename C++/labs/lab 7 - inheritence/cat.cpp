#include <string.h>

#include "cat.h"

Cat::Cat(const char* name, const char* color, float whiskersLen) : whiskersLen(whiskersLen)
{
	this->name = strdup(name);
	this->color = strdup(color);
}

Cat::Cat(const Cat& other) : name(NULL), color(NULL)
{
	*this = other;
}

Cat::Cat(Cat&& other) : name(NULL), color(NULL)
{
	*this = std::move(other);
}
Cat::~Cat()
{
	delete []name;
	delete []color;
}

const Cat& Cat::operator=(const Cat& other)
{
	if (this != &other)
	{
		setName(other.name);
		setColor(other.color);
		setWhiskersLen(other.whiskersLen);
	}
	return *this;
}

const Cat& Cat::operator=(Cat&& other)
{
	if (this != &other)
	{
		whiskersLen = other.whiskersLen;
		std::swap(name, other.name);
		std::swap(color, other.color);
	}
	return *this;
}

void Cat::setName(const char* name)
{
	delete []this->name;
	this->name = strdup(name);
}

void Cat::setColor(const char* color)
{
	delete []this->color;
	this->color = strdup(color);
}

void Cat::setWhiskersLen(float whiskersLen)
{
	this->whiskersLen = whiskersLen;
}

ostream& operator<<(ostream& os, const Cat& cat)
{
	os << "Name: " << cat.name << "\tColor: " << cat.color << "\tWhiskersLenLen: " << cat.whiskersLen;
	return os;
}
