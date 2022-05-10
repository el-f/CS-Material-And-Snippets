#ifndef __SET_H
#define __SET_H

#include <iostream>
using namespace std;

class Set
{
public:
	Set(int maxSize=1000);
	Set(const Set& other);
	Set(Set&& other);
	~Set();

	friend Set operator+(int newVal, const Set& set);
	friend Set operator+(const Set& set, int newVal);

	Set        operator+(const Set& other)  const;
	const Set& operator+=(int newVal);
	const Set& operator=(const Set& other);
	const Set& operator=(Set&& other);
	bool       operator>(const Set& other)  const;
	int&       operator[](int index);
	const int& operator[](int index) const;
	bool       operator==(const Set& other) const;

	bool exists(int value) const;

	friend ostream& operator<<(ostream& os, const Set& obj);

private:
	int  maxSize;
	int  currentSize;
	int* arr;
};

#endif // __SET_H