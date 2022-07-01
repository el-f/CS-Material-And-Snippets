#ifndef __ENTRY_H
#define __ENTRY_H

#include "component.h"

class Entry : public Component
{
public:
	Entry(const string& name, const string& adddress, const string& phone);

	virtual void       show()  const override; // in usage of composite design pattern
	virtual Component* clone() const override; // for prototype design pattern

private:
	string name;
	string address;
	string phone;
};

#endif // __ENTRY_H