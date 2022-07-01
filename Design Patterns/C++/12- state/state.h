#ifndef __STATE_H
#define __STATE_H

#include <iostream>
using namespace std;

#include "machine.h"

class State
{
public:
	virtual void on(Machine& m) const
	{
		cout << "   already ON\n";
	}

	virtual void off(Machine& m) const
	{
		cout << "   already OFF\n";
	}
};  // State

#endif // __STATE_H