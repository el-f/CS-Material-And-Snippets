#ifndef __MACHINE_H
#define __MACHINE_H

class State;

class Machine
{
public:
	Machine();
	~Machine();

	void setCurrent(State *s)	{current = s;}
	void on();
	void off();
private:
	State* current;
};

#endif // __MACHINE_H