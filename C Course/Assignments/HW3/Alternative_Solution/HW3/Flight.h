#ifndef __FLIGHT__
#define __FLIGHT__

#include "AirportManager.h"
#include "Date.h"

typedef struct
{
	char		originCode[CODE_LENGTH + 1];
	char		destCode[CODE_LENGTH + 1];
	int			hour;
	Date		date;
}Flight;

int		isFlightInRoute(const Flight* pFlight, const char* codeSource, const char* codeDest);
int		countFlightsInRoute(Flight** arr, int size,const char* codeSource, const char* codeDest);
void	printFlight(const Flight* pFlight);
void	printFlightV(const void* val);

void	initFlight(Flight* pFlight,const AirportManager* pManager);
int		getFlightHour();
Airport*	setAiportToFlight(const AirportManager* pManager, const char* msg);

void	freeFlight(void* val);

int		loadFlightFromFile(Flight* pF, const AirportManager* pManager, FILE* fp);
int		saveFlightToFile(const Flight* pF, FILE* fp);

int		compareByCodeOrig(const void* air1, const void* air2);
int		compareByCodeDest(const void* air1, const void* air2);
int		compareByHour(const void* air1, const void* air2);
int		compareByDate(const void* air1, const void* air2);

#endif
