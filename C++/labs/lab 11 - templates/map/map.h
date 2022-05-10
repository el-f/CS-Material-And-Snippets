#ifndef __MAP_H
#define __MAP_H

#pragma warning(disable: 4290)

#include <iostream>
using namespace std;

template <class K, class V>
class Map
{
public:
	static const int MAX_SIZE = 3;

	class Pair
	{
	private:
		K key;
		V value;
	public:
		Pair() {}
		Pair(const K& k, const V& v) : key(k), value(v) {}

		const K& getKey()   const {return key;}
		const V& getValue() const {return value;}
		      V& getValue()       {return value;}

		void setKey  (const K& k) {key   = k;}
		void setValue(const V& v) {value = v;}

		friend ostream& operator<<(ostream& os, const Pair& m)
		{
			os << m.key << " --> " << m.value;
			return os;
		}
	};
private:
	Pair theMap[MAX_SIZE];
	int  size;

public:

	Map();

	V& operator[](const K& key) throw (const char*);
	
	bool isKeyExists(const K& key) const;

	friend ostream& operator<<(ostream& os, const Map& m)
	{
		for (int i = 0; i < m.size; i++)
			os << m.theMap[i] << endl;
		return os;
	}
}; // class Map

template <class K, class V>
Map<K,V>::Map() : size(0)
{
}

template <class K, class V>
bool Map<K,V>::isKeyExists(const K& key) const
{
	for (int i=0 ; i < size ; i++)
	{
		if (theMap[i].key == key)
			return true;
	}
	return false;
}

template <class K, class V>
V& Map<K,V>::operator[](const K& key) throw (const char*)
{
	for (int i=0 ; i < size ; i++)
		if (theMap[i].getKey() == key)
			return theMap[i].getValue();

	if (size >= MAX_SIZE)
		throw "Map is full";

	theMap[size].setKey(key);
	return theMap[size++].getValue();
}

#endif // __MAP_H