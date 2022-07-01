#include "on.h"
#include "off.h"

void On::off(Machine& m) const
{
	cout << "   going from ON to OFF";
	m.setCurrent(new Off());
	delete this;
}