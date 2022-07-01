#include <iostream>
using namespace std;

#include <time.h>

#include "trafficLightManager.h"
#include "trafficLightState.h"

void sleep(int milliseconds) // Cross-platform sleep function
{
	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end)
	{
	}
}

int main()
{
	TrafficLightManager tlm;

	for (int i=0 ; i < 10 ; i++)
	{
		tlm.handle();
		sleep(1000);
	}

	cout << "END" << endl;
}