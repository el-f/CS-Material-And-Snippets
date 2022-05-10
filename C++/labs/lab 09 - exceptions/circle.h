#ifndef __CIRCLE_H
#define __CIRCLE_H

#pragma warning(disable: 4996)

#include "shape.h"
#include "ShapeException.h"

class Circle : public Shape
{
protected:
	constexpr static float PI = 3.14f;

	float radius;

public:
	Circle(float frameWidth, const char* color, float radius) throw (CircleException);

	virtual void toOs(ostream& os) const override;

	virtual float getArea() const override;
	virtual float getPerimeter() const override;
};

#endif