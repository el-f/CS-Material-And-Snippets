#ifndef __SURVIVOR_H
#define __SURVIVOR_H

class Survivor
{
public:
	enum class eStatus {Single, Married, InARelationship };
private:
	char name[20];
	int age;
	eStatus theStatus;

public:
	void init(const char* n, int a, eStatus s);
	void print() const;
};

#endif // __SURVIVOR_H