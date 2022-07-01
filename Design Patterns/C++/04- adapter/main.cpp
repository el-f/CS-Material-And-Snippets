#include <iostream>
using namespace std;

// Desired interface
class Rectangle
{
public:
	virtual void draw() const = 0;
};

// Legacy component, the adaptee
class LegacyRectangle
{
public:
	LegacyRectangle(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2)
	{
		cout << "LegacyRectangle:  create.  (" << x1 << "," << y1 << ") => ("
			<< x2 << "," << y2 << ")" << endl;
	}
	void oldDraw() const
	{
		cout << "LegacyRectangle:  oldDraw.  (" << x1 << "," << y1 << 
			") => (" << x2 << "," << y2 << ")" << endl;
	}
private:
	int x1, y1, x2, y2;
}; // Legacy component

// the adapter wrapper
class RectangleAdapter: public Rectangle
{
public:
	RectangleAdapter(int x, int y, int w, int h) : lr(x, y, x + w, y + h)
	{
		cout << "RectangleAdapter: create.  (" << x << "," << y <<  
		  "), width = " << w << ", height = " << h << endl;
	}

	virtual void draw() const override
	{
	  cout << "RectangleAdapter: draw." << endl;
	  lr.oldDraw();
	}

private:
	LegacyRectangle lr;
};

int main()
{
	Rectangle* r = new RectangleAdapter(120, 200, 60, 40);
	r->draw();
	delete r;
}
