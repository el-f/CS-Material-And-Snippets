#include <iostream>
using namespace std;

#include "trafficLightManager.h"
#include "trafficLightState.h"

TrafficLightManager::TrafficLightManager()
{
	currentColor = &TrafficLightRed::getInstance();
	cout << "TrafficLightManager is started. color=RED\n";
}

void TrafficLightManager::handle()
{
	currentColor->changeColor(*this);
}

void TrafficLightManager::changeCurrentColor(TrafficLightState* newColor)
{
	currentColor = newColor;
}