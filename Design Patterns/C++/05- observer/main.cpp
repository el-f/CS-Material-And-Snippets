#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Observer
{
public:
	Observer(const string& name) : name(name) {}
	virtual void notify(const string& name, int precentage) const = 0;
	virtual Observer* clone() const =0;
	const string& getName() const {return name;}
protected:
	string name;
}; // Observer

class Shop {
public:
	Shop(const string& name) : name(name) {}

	void registerObserver(Observer* obs) 
	{
		cout << "Registerd " << obs->getName() << " to get notifications from '" << name << "'\n";
		viewers.push_back(obs);
	}
	void setSale(int precenatge) 
	{
		cout << "Set " << precenatge << "% sale on '" << name << "'\n";
		notifyAllRegistered(precenatge);
	}

private:
	void notifyAllRegistered(int precenatge) const
	{
		vector<Observer*>::const_iterator itr    = viewers.begin();
		vector<Observer*>::const_iterator itrEnd = viewers.end();
		for (; itr != itrEnd; ++itr)
			(*itr)->notify(name, precenatge);
	}

	string name;
	vector<Observer*> viewers; 
};

class Customer : public Observer 
{
public:
	Customer(const string& name) : Observer(name) {}
	virtual void notify(const string& shopName, int precentage) const override
	{
		cout << name << "! There is " << precentage << "% sale on '" << shopName << "'\n";
	}

	virtual Observer* clone() const override {return new Customer(*this);}
};

class Newspaper : public Observer 
{
public:
	Newspaper(const string& name) : Observer(name) {}
	virtual void notify(const string& shopName, int precentage) const override
	{
		cout << "The newspaper " << name << " prints add that there is " << precentage << "% sale on '" << shopName << "'\n";
	}

	virtual Observer* clone() const override {return new Newspaper(*this);}
};


void main() 
{
	Shop s1("H&M");
	Shop s2("ZARA");
	Shop s3("Pull and Bear");

	Customer c1("Gogo");
	Customer c2("Momo");
	Newspaper n1("Yediot");
	Newspaper n2("Ma'ariv");

	s1.registerObserver(&c1);
	s1.registerObserver(&c2);
	s1.registerObserver(&n1);
	s1.registerObserver(&n2);

	s2.registerObserver(&c1);
	s2.registerObserver(&n1);
	s2.registerObserver(&n2);

	s3.registerObserver(&c2);
	s3.registerObserver(&n1);
	s3.registerObserver(&n2);
	cout << "\n";

	s1.setSale(50);
	s2.setSale(20);
	s3.setSale(30);
	cout << "\n";
}