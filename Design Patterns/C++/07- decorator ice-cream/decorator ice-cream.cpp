#include <iostream>
#include <string>
using namespace std;

class IceCreamParts
{
protected:
	IceCreamParts() {}
public:
	virtual void draw() const = 0;
};

class IceCream : public IceCreamParts
{
	int numOfBalls;
	string flavor;
public:
	IceCream(int numOfBalls, const string& flavor) : numOfBalls(numOfBalls), flavor(flavor) {}

	virtual void draw() const override
	{
		cout << "IceCream " << flavor << " with " << numOfBalls << " balls";
	}
};

class IceCreamTopping : public IceCreamParts
{
	IceCreamParts* iceCreamPart;
public:
	IceCreamTopping(IceCreamParts* iceCreamPart) : iceCreamPart(iceCreamPart) {}
	~IceCreamTopping() { delete iceCreamPart; }

	virtual void draw() const override
	{
		iceCreamPart->draw();
	}
};

class HotChocolate : public IceCreamTopping
{
	int grams;
public:
	HotChocolate(IceCreamParts* iceCreamPart, int grams) : IceCreamTopping(iceCreamPart), grams(grams) {}
	virtual void draw() const
	{
		IceCreamTopping::draw();
		cout << ", " << grams << " grams of HotChocolate";
	}
};

class WhippedCream : public IceCreamTopping
{
	string color;
public:
	WhippedCream(IceCreamParts* iceCreamPart, const string& color) : IceCreamTopping(iceCreamPart), color(color) {}
	virtual void draw() const override
	{
		IceCreamTopping::draw();
		cout << ", " << color << " whipped cream";
	}
};

int main()
{
	IceCreamParts* ice1 = new IceCream(3, "Vanilla");
	ice1->draw();
	cout << endl;

	IceCreamParts* ice2 = new HotChocolate(
		new WhippedCream(
			new IceCream(2, "Chococlate"), "white"), 30);
	ice2->draw();
	cout << endl;

	IceCreamParts* ice3 = new HotChocolate(
		new WhippedCream(
			new HotChocolate(new IceCream(1, "Vanilla"), 50), "white"), 
		30);
	ice3->draw();
	cout << endl;

	delete ice1;
	delete ice2;
	delete ice3;
}