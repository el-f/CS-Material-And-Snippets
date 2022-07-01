#include <iostream>
using namespace std;

#include "category.h"

Category::Category(const string& name) : name(name), numOfComponents(0) {}

Category::Category(const Category& other)
{
	*this = other;
}

Category::~Category()
{
	for (int i=0 ; i < numOfComponents ; i++)
		delete components[i];
}

void Category::show() const
{
	cout << name.c_str() << ":\n";
	for (int i=0 ; i < numOfComponents ; i++)
	{
		components[i]->show();
		cout << endl;
	}
}

void Category::addComponent(const Component& newComponent) 
{
	if (numOfComponents < MAX_COMPONENTS)
		components[numOfComponents++] = newComponent.clone();
}

Component* Category::getComponentAtIndex(int index) const
{
	return components[index]->clone();
}

Component* Category::clone() const 
{
	return new Category(*this);
}

const Category& Category::operator=(const Category& other)
{
	if (this != &other)
	{
		for (int i=0 ; i < numOfComponents ; i++)
			delete components[i];

		numOfComponents = other.numOfComponents;
		for (int i=0 ; i < numOfComponents ; i++)
			components[i] = other.components[i]->clone();

		name = other.name;
	}
	return *this;
}
