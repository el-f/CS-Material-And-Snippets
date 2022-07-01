#ifndef __TRAFFIC_LIGHT_STATE_H
#define __TRAFFIC_LIGHT_STATE_H

#include "trafficLightManager.h"

class TrafficLightState
{
public:
	virtual void changeColor(TrafficLightManager& tlm) = 0;
};

class TrafficLightRed : public TrafficLightState
{
public:
	virtual void changeColor(TrafficLightManager& tlm) override;
};

class TrafficLightYellow : public TrafficLightState
{
public:
	virtual void changeColor(TrafficLightManager& tlm) override;
};

class TrafficLightGreen : public TrafficLightState
{
public:
	virtual void changeColor(TrafficLightManager& tlm) override;
};

#endif // __TRAFFIC_LIGHT_STATE_H
