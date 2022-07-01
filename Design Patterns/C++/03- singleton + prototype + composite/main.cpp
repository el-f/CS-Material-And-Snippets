#include <iostream>
using namespace std;

#include "yellowPages.h"
#include "entry.h"

/*
Demonstrating the following patterns:
	Singleton
	Prototype (Virtual Constructor)
	Composite
*/
void main()
{
	cout << "Enter main\n";
	
	YellowPages* yp = YellowPages::getInstance();
	
	Category c1("food");
	Category c11("chinese"), c12("fast food");
	c11.addComponent(Entry("Pekin", "sne 29 Tel-Aviv", "03-6479087"));
	c11.addComponent(Entry("Yakuza", "Dizengof 3 Tel-Aviv", "03-5247412"));
	c12.addComponent(Entry("Dominos", "Tagur 5 Tel-Aviv", "03-6411254"));
	c1.addComponent(c11);
	c1.addComponent(c12);

	yp->addCategory(c1);
	yp->show();

	cout << "Exit main\n";
}