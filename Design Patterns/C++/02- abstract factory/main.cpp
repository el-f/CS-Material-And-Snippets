#include <iostream>
using namespace std;

/*
This example demonstartes the Abstract Factory pattern
*/

class Herbivore
{
protected:
	Herbivore() {}
public:
	virtual ~Herbivore() {} // WHY DO WE NEED THE VIRTUAL D'TOR??
};

class Carnivore
{
protected:
	Carnivore() {}
public:
	virtual ~Carnivore() {}

	virtual void eat(Herbivore* h) 
	{
		// Eat Wildebeest - or any other Harbivore type
		cout << typeid(*this).name()+6 << " eats " << typeid(*h).name()+6 << endl;
	}
};

class Wildebeest : public Herbivore
{
};

class Lion : public Carnivore
{
};

class Bison : public Herbivore
{
};

class Wolf : public Carnivore
{
};

class ContinentFactory
{
public:
	virtual ~ContinentFactory() {}

	virtual Herbivore* createHerbivore() = 0;	
	virtual Carnivore* createCarnivore() = 0;
};


class AfricaFactory : public ContinentFactory
{
public:
	virtual Herbivore* createHerbivore() override {return new Wildebeest();}
	virtual Carnivore* createCarnivore() override {return new Lion();}
};

class AmericaFactory : public ContinentFactory
{
public:
	virtual Herbivore* createHerbivore() override {return new Bison();}
	virtual Carnivore* createCarnivore() override {return new Wolf();}
};

class AnimalWorld
{
public:
	AnimalWorld(ContinentFactory& factory)
	{
		carnivore = factory.createCarnivore();
		herbivore = factory.createHerbivore();
	}

	~AnimalWorld()
	{
		delete herbivore;
		delete carnivore;
	}

	void runFoodChain()
	{
		carnivore->eat(herbivore);
	}

private:
	Herbivore* herbivore;
	Carnivore* carnivore;
};

int main()
{
	// Create and run the Africa animal world 
	ContinentFactory* africa = new AfricaFactory();
	AnimalWorld world1(*africa);
	world1.runFoodChain();

	// Create and run the America animal world 
	ContinentFactory* america = new AmericaFactory();
	AnimalWorld world2(*america);
	world2.runFoodChain();

	delete africa;
	delete america;
}
