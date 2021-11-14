#ifndef __AIRPORT__
#define __AIRPORT__

#define CODE_LENGTH 3

typedef struct
{
	char*	name;
	char*	country;
	char	code[CODE_LENGTH+1];
}Airport;

int		isSameAirport(const Airport* pPort1, const Airport* pPort2);
int		compareAirport(const void* e1, const void* e2);
int		isAirportCode(const Airport* pPort1, const char* code);
void	printAirport(const void* e1);
void	initAirportNoCode(Airport* pPort);
void    getAirportCode(char* code);
void	getAirportName(Airport* pPort);
char*	fixName(char* str);
void	changeEvenWord(char* str);
void	freeAirport(void* e1);

int		saveAirportToFile(const Airport* pAir, FILE* fp);
int		loadAirportFromFile(Airport* pAir, FILE* fp);

#endif