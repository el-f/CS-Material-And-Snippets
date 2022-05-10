#include "set.h"

Set::Set(int maxSize) : maxSize(maxSize), currentSize(0)
{
	arr = new int[maxSize];
}

Set::Set(const Set& other) : arr(NULL)
{
	*this = other;
}

Set::Set(Set&& other)
{
	this->maxSize = other.maxSize;
	this->currentSize = other.currentSize;
	this->arr = other.arr;
	other.arr = nullptr;
}

Set::~Set()
{
	delete []arr;
}

const Set& Set::operator=(const Set& other)
{
	if (this != &other)
	{
		delete []arr;
		maxSize = other.maxSize;
		currentSize = other.currentSize;
		arr = new int[maxSize];
		for (int i=0 ; i < currentSize ; i++)
			arr[i] = other.arr[i];
	}
	return *this;
}

const Set& Set::operator=(Set&& other)
{
	if (this != &other)
	{
		maxSize = other.maxSize;
		currentSize = other.currentSize;
		std::swap(this->arr, other.arr);
	}
	return *this;
}
const Set& Set::operator+=(int newVal)
{
	if (!exists(newVal))
		arr[currentSize++] = newVal;

	return *this;
}

Set operator+(int newVal, const Set& set)
{
	return set+newVal;
}

Set operator+(const Set& set, int newVal)
{
	if (set.exists(newVal))
		return set;

	Set temp(set);
	temp.arr[temp.currentSize++] = newVal;
	return temp;
}

Set Set::operator+(const Set& other) const
{
	Set temp(currentSize+other.currentSize);

	for (int i=0 ; i < currentSize ; i++)
		temp += arr[i];

	for (int i=0 ; i < other.currentSize ; i++)
		temp += other.arr[i];

	return temp;
}

bool Set::exists(int value) const
{
	for (int i=0 ; i < currentSize ; i++)
		if (arr[i] == value)
			return true;

	return false;
}

bool Set::operator>(const Set& other) const
{
	return currentSize > other.currentSize;
}

int& Set::operator[](int index)
{
	return arr[index];
}

const int& Set::operator[](int index) const
{
	return arr[index];
}

bool Set::operator==(const Set& other) const
{
	if (currentSize != other.currentSize)
		return false;

	for (int i=0 ; i < currentSize ; i++)
	{
		if (!other.exists(arr[i]))
			return false;
	}
	return true;

}

ostream& operator<<(ostream& os, const Set& obj)
{
	for (int i=0 ; i < obj.currentSize ; i++)
		os << obj.arr[i] << " ";

	return os;
}
