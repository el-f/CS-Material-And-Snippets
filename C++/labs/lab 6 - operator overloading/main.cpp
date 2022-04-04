#include <iostream>
using namespace std;

#include "set.h"

int main()
{

	Set s1, s2, s3, s4;

	for (int i=1 ; i <= 5 ; i++)
	{
		s1 += i;
		s1 += i;
		s4 += i;
	}
	cout << "s1 is: " << s1 << endl;
	cout << "s4 is: " << s4 << endl;

	for (int i=3 ; i <= 8 ; i++)
	{
		s2 += i;
	}
	cout << "s2 is: " << s2 << endl;

	s3 = s1 + s2;
	s3 = s1 + 10;
	s3 = 12 + s1;
	cout << "s3 is: " << s3 << endl;

	s2 = s1;
	cout << "s2 after getting s1 values: " << s2 << endl;

	cout << "s3 > s1 ? " << (s3 > s1 ? "true" : "false") << endl;
	cout << "s1 > s3 ? " << (s1 > s3 ? "true" : "false") << endl;
	cout << "s1 == s4 ? " << (s1 == s4 ? "true" : "false") << endl;
	cout << "s1 == s3 ? " << (s1 == s3 ? "true" : "false") << endl;

	cout << "Element in index 3 in s1 is " << s1[3] << endl;
	s1[3] = -1;
	cout << "Element in index 3 in s1 after setting to -1 is " << s1[3] << endl;
	
	return 0;
}