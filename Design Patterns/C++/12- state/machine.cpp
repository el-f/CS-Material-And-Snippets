#include "machine.h"
#include "state.h"

#include "on.h"
#include "off.h"

Machine::Machine()
{
	current = new Off();
	cout << "Machine is started. state=off\n";
}

Machine::~Machine() 
{
	delete current;
}

void Machine::on()  
{
	current->on(*this);
}

void Machine::off() 
{
	current->off(*this);
}