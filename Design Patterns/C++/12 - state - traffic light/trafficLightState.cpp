#include <iostream>
using namespace std;

#include "trafficLightState.h"

void TrafficLightRed::changeColor(TrafficLightManager& tlm)
{
	cout << "   Change color from RED to YELLOW\n";
	tlm.changeCurrentColor(new TrafficLightYellow());
	delete this;
}

void TrafficLightYellow::changeColor(TrafficLightManager& tlm)
{
	cout << "   Change color from YELLOW to GREEN\n";
	tlm.changeCurrentColor(new TrafficLightGreen());
	delete this;
}

void TrafficLightGreen::changeColor(TrafficLightManager& tlm)
{
	cout << "   Change color from GREEN to RED\n";
	tlm.changeCurrentColor(new TrafficLightRed());
	delete this;
}