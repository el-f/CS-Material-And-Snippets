#include "off.h"
#include "on.h"

void Off::on(Machine& m) const
{
	cout << "   going from OFF to ON";
	m.setCurrent(new On());
	delete this;
}