#ifndef __SQUARE_H
#define __SQUARE_H

#include "shape.h"

class Square : public Shape
{
private:
	double len;

public:
	Square(const char* color, int width, int len) : Shape(color, width)
	{
		this->len = len;
	}

	virtual double getPerimeter() const override
	{
		return 4 * len;
	}

	virtual double getArea() const override
	{
		return len * len;
	}

	virtual void toOs(ostream& os) const override {
		os << ", len=" << len;
	}

	void draw() const
	{
		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < len; j++)
				cout << "*";
			cout << endl;
		}
		cout << endl;
	}
};
#endif // __SQUARE_H