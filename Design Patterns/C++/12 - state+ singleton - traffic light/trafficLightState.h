#ifndef __TRAFFIC_LIGHT_STATE_H
#define __TRAFFIC_LIGHT_STATE_H

#include "trafficLightManager.h"

class TrafficLightState
{
protected:
	TrafficLightState() {} 
public:
	virtual void changeColor(TrafficLightManager& tlm) = 0;
};


class TrafficLightRed : public TrafficLightState
{
private:
	static TrafficLightRed theInstance;
	TrafficLightRed() {}  // for singleton
public:
	virtual void changeColor(TrafficLightManager& tlm) override; 
	static TrafficLightRed& getInstance() { return theInstance; }
};

class TrafficLightYellow : public TrafficLightState
{
private:
	static TrafficLightYellow theInstance;
	TrafficLightYellow() {}  // for singleton
public:
	virtual void changeColor(TrafficLightManager& tlm) override;
	static TrafficLightYellow& getInstance() { return theInstance; }

	friend class TrafficLightManager; // so it could create the intialized traffic light, the c'tor is private
};

class TrafficLightGreen : public TrafficLightState
{
private:
	static TrafficLightGreen theInstance;
	TrafficLightGreen() {}  // for singleton
public:
	virtual void changeColor(TrafficLightManager& tlm) override;
	static TrafficLightGreen& getInstance() { return theInstance; }

	friend class TrafficLightManager; // so it could create the intialized traffic light, the c'tor is private
};

#endif // __TRAFFIC_LIGHT_STATE_H
