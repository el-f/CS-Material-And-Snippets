#ifndef __Component_H
#define __Component_H

#include <iostream>
using namespace std;

class Component
{
public:
	virtual void show() const =0;  // in usage of composite design pattern
	virtual Component* clone() const =0; // for prototype design pattern
};

#endif // __Component_H