#ifndef __SURVIVOR_H
#define __SURVIVOR_H

class Survivor
{
private:
	char name[20];
	int age;

public:
	void init(const char* n, int a);
	void print();
};

#endif // __SURVIVOR_H