#ifndef __ON_H
#define __ON_H

#include "state.h"

class On :	public State
{
public:
	On()    {cout << "   ON-ctor\n";}
	~On()   {cout << "   dtor-ON\n";}
	virtual void off(Machine& m) const;
};

#endif // __ON_H
