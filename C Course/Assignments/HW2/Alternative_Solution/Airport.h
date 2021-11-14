#ifndef __AIRPORT__
#define __AIRPORT__

#include "General.h"

typedef struct
{
	char*	name;
	char*	country;
	char	code[CODE_LENGTH+1];
}Airport;

int		isSameAirport(const Airport* pPort1, const Airport* pPort2);
int		isAirportCode(const Airport* pPort1, const char* code);
void	initAirportNoCode(Airport* pPort);
void	printAirport(const Airport* pPort);
void	getAirportName(Airport* pPort);
void	changeEvenWord(char* str);
void    getAirportCode(char* code);
void	freeAirport(Airport* pPort);

#endif