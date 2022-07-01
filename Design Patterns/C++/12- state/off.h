#ifndef __OFF_H
#define __OFF_H

#include "state.h"

class Off :	public State
{
public:
	Off()    {cout << "   OFF-ctor\n";}
	~Off()   {cout << "   dtor-OFF\n";};
	virtual void on(Machine& m) const;
};

#endif // __OFF_H
