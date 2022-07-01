#include <iostream>
using namespace std;

#include "trafficLightState.h"

TrafficLightRed    TrafficLightRed::theInstance;
TrafficLightYellow TrafficLightYellow::theInstance;
TrafficLightGreen  TrafficLightGreen::theInstance;

void TrafficLightRed::changeColor(TrafficLightManager& tlm)
{
	cout << "   Change color from RED to YELLOW\n";
	tlm.changeCurrentColor(&TrafficLightYellow::getInstance());
}

void TrafficLightYellow::changeColor(TrafficLightManager& tlm)
{
	cout << "   Change color from YELLOW to GREEN\n";
	tlm.changeCurrentColor(&TrafficLightGreen::getInstance());
}

void TrafficLightGreen::changeColor(TrafficLightManager& tlm)
{
	cout << "   Change color from GREEN to RED\n";
	tlm.changeCurrentColor(&TrafficLightRed::getInstance());
}