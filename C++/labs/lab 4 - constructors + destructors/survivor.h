#ifndef __SURVIVOR_H
#define __SURVIVOR_H

class Survivor
{
public:
	enum class eStatus {Single, Married, InARelationship };
private:
	char* name;
	int age;
	eStatus theStatus;

public:
	Survivor(const char* n, int a, eStatus s);
	Survivor(const Survivor& other) = delete;
	~Survivor();

	void print() const;

	bool setName(const char* n);
};

#endif // __SURVIVOR_H