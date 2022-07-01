#include <iostream>
using namespace std;

#include "machine.h"

int main()
{
	Machine m;
	int answer;
	bool fContinue = true;

	while (fContinue)
	{
		cout << "Enter 0/1, 2 to exit: ";
		cin >> answer;

		switch (answer)
		{
		case 0:
			m.off();
			break;
		case 1:
			m.on();
			break;
		case 2:
			fContinue = false;
		}
	}
}
