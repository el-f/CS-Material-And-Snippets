#ifndef __SURVIVOR_H
#define __SURVIVOR_H

#include "bandana.h"

class Tribe;

class Survivor
{
public:
	enum class eStatus {Single, Married, InARelationship };
private:
	char* name;
	int age;
	eStatus theStatus;
	Bandana theBandana;
	int serialNumber;
	static int numberGenerator;
	const Tribe* theTribe;

public:
	Survivor(const char* name, int age, eStatus status, const Tribe& theTribe);
	Survivor(const Survivor& other) = delete;
	~Survivor();

	void print() const;

	bool setName(const char* name);
};

#endif // __SURVIVOR_H