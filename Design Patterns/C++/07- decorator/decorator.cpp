#include <iostream>
#include <string>
using namespace std;

class Shapeable
{
public:
	virtual void draw() const =0;
};

class Shape : public Shapeable
{
	int numOfPoints;
	string name;

public:
	Shape(int numOfPoints, const string& name) : numOfPoints(numOfPoints), name(name) {}

	virtual void draw() const =0
	{
		cout << "The shape is " << name << ", numOfPoints=" << numOfPoints;
	}
};

class Circle : public Shape
{
	int radius;

public:
	Circle(int numOfPoints, const string& name, int radius) : Shape(numOfPoints, name), radius(radius) {}

	virtual void draw() const override
	{
		Shape::draw();
		cout << ", radius=" << radius;
	}
};

class ShapeProperty : public Shapeable
{
	Shapeable* theShape;
public:
	ShapeProperty(Shapeable* theShape) : theShape(theShape) {}
	~ShapeProperty() { delete theShape; }

	virtual void draw() const override
	{
		theShape->draw();
	}
};

class ShapeWithBorder : public ShapeProperty
{
	
	int borderLength;
public:
	ShapeWithBorder(Shapeable* theShape, int borderLength) : ShapeProperty(theShape), borderLength(borderLength) {}
	virtual void draw() const
	{
		ShapeProperty::draw();
		cout << ", border=" << borderLength;
	}
};

class ShapeWithColor : public ShapeProperty
{
	string color;
public:
	ShapeWithColor(Shapeable* theShape, const string& color) : ShapeProperty(theShape), color(color) {}
	virtual void draw() const override
	{
		ShapeProperty::draw();
		cout << ", color=" << color;
	}
};

int main()
{
	Shapeable* s1 = new Circle(0, "circle", 5);
	s1->draw();
	cout << endl;

	Shapeable* s2 = new ShapeWithBorder(
		new ShapeWithColor(
		new Circle(0, "circle", 5), "red"), 2);
	s2->draw();
	cout << endl;

	Shapeable* s3 = new ShapeWithColor(
		new ShapeWithBorder(
			new Circle(0, "circle", 5), 7), "blue");
	s3->draw();
	cout << endl;

	delete s1;
	delete s2;
	delete s3;
}