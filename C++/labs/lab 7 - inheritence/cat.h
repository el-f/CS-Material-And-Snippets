#ifndef __CAT_H
#define __CAT_H

#include <iostream>
using namespace std;

class Cat
{
protected:
	char* name;
	char* color;
	float whiskersLen;

public:
	Cat(const char* name, const char* color, float whiskersLen);
	Cat(const Cat& other);
	Cat(Cat&& other);
	~Cat();

	const Cat& operator=(const Cat& other);
	const Cat& operator=(Cat&& other);

	void setName(const char* name);
	void setColor(const char* color);
	void setWhiskersLen(float whiskersLen);

	const char* getName()       const {return name;}
	const char* getColor()      const {return color;}
	float       getWhiskersLen() const {return whiskersLen;}

	friend ostream& operator<<(ostream& os, const Cat& cat);
};

#endif // __CAT_H