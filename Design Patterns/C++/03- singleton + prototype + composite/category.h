#ifndef __CATEGORY
#define __CATEGORY

#include "component.h"

class Category : public Component
{
public:
	static const int MAX_COMPONENTS = 100;

	Category(const string& name);
	Category(const Category& other);
	~Category();

	const Category& operator=(const Category&); 

	virtual Component* clone() const override; // for prototype design pattern

	virtual void show() const override; // in usage of composite design pattern

	void addComponent(const Component& newComponent); // in usage of composite design pattern
	Component* getComponentAtIndex(int index) const; // in usage of composite design pattern
private:
	string name;
	Component* components[MAX_COMPONENTS]; // in usage of composite design pattern
	int numOfComponents;
};

#endif // __CATEGORY