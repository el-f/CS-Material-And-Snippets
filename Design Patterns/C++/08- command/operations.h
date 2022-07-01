#ifndef _OPER_H
#define _OPER_H

#pragma warning (disable : 4786)

#include <map>
using namespace std;

class Operator;

class Operations
{
	map<char,Operator*> allOperations;
	float currentValue;
public:

	Operations();

	Operator* operate(char operand, float number, bool isUndoable);
};

class Operator
{
protected:
	float val;
	Operations* theOperations;
public:

	Operator(Operations* theOperations) : val(0) , theOperations(theOperations) {}

	virtual void execute(float value, float &total) = 0;
	virtual void execute()                          = 0;
	virtual void unExecute()                        = 0;
	
	virtual Operator* clone()                       = 0;
};

class Plus : public Operator
{
public:
	Plus(Operations* theOperations) : Operator(theOperations) {}

	virtual void execute(float value, float &total) override;
	virtual void execute() override;
	virtual void unExecute() override;

	virtual Operator* clone() override;
};

class Minus : public Operator
{
public:
	Minus(Operations* theOperations) : Operator(theOperations) {}

	virtual void execute(float value, float &total) override;
	virtual void execute() override;
	virtual void unExecute() override;

	virtual Operator* clone() override;
};

class Multiply : public Operator
{
public:
	Multiply(Operations* theOperations) : Operator(theOperations) {}

	virtual void execute(float value, float &total) override;
	virtual void execute() override;
	virtual void unExecute() override;

	virtual Operator* clone() override;
};

class Divide : public Operator
{
public:
	Divide(Operations* theOperations) : Operator(theOperations) {}

	virtual void execute(float value, float &total) override;
	virtual void execute() override;
	virtual void unExecute() override;
	
	virtual Operator* clone() override;
};

#endif