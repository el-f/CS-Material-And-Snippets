#pragma warning (disable : 4786)
#include <iostream>
using namespace std;

#include "Operations.h"

Operations::Operations()
{
	currentValue = 0;
	allOperations['+'] = new Plus(this);
	allOperations['-'] = new Minus(this);
	allOperations['*'] = new Multiply(this);
	allOperations['/'] = new Divide(this);
}

Operator* Operations::operate(char operand, float number , bool isUndoable)
{
	float oldVal = currentValue;

	map<char,Operator*>::iterator itr = allOperations.find(operand);
	
	if(itr == allOperations.end())
		throw 0;
	
	((*itr).second)->execute(number , currentValue);
	
	cout << oldVal << " " << operand << " " << number << " = " << currentValue << endl;			
	
	return isUndoable ? ((*itr).second)->clone() : nullptr;
}


void Plus::execute(float value, float &total)
{
	total += value;
	val = value;
}

void Plus::unExecute()
{
	theOperations->operate('-' , val , false);
}
	
void Plus::execute()
{
	theOperations->operate('+' , val , false);
}	

Operator* Plus::clone()
{
	return new Plus(*this);
}

void Minus::execute(float value, float &total)
{
	total -= value;
	val = value;
}

void Minus::unExecute()
{
	theOperations->operate('+', val, false);
}
	
void Minus::execute()
{
	theOperations->operate('-', val, false);
}

Operator* Minus::clone()
{
	return new Minus(*this);
}


void Multiply::execute(float value, float &total)
{
	total *= value;
	val = value;
}

void Multiply::unExecute()
{
	theOperations->operate('/', val, false);
}
	
void Multiply::execute()
{
	theOperations->operate('*', val, false);
}	

Operator* Multiply::clone()
{
	return new Multiply(*this);
}

void Divide::execute(float value, float &total)
{
	total /= value;
	val = value;
}

void Divide::unExecute()
{
	theOperations->operate('*', val, false);
}
	
void Divide::execute()
{
	theOperations->operate('/', val, false);
}	

Operator* Divide::clone()
{
	return new Divide(*this);
}


