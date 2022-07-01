#ifndef __TRAFFIC_LIGHT_MANAGER_H
#define __TRAFFIC_LIGHT_MANAGER_H

class TrafficLightState;

class TrafficLightManager
{
	TrafficLightState* currentColor;

public:
	TrafficLightManager();

	void handle();
	void changeCurrentColor(TrafficLightState* newColor);
};

#endif // __TRAFFIC_LIGHT_MANAGER_H