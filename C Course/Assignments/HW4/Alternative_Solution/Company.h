#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"
#include "GeneralList.h"

#define COMP_SAVE
#define COMP_LOAD

typedef enum { eNone, eHour, eDate,eSorceCode,eDestCode, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt];


typedef struct
{
	char*		name;
	int			flightCount;
	Flight**	flightArr;
	eSortOption	sortOpt;
	LIST		flighDateList;
}Company;

int		initCompanyFromFile(Company* pComp, AirportManager* pManaer, const char* fileName);
void	initCompany(Company* pComp, AirportManager* pManaer);
void	initDateList(Company* pComp);
int		isUniqueDate(const Company* pComp, int index);
int		addFlight(Company* pComp,const AirportManager* pManager);

void	printCompany(const Company* pComp,char* add, ...);
void	printFlightsCount(const Company* pComp);

int		saveCompanyToFile(const Company* pComp, const char* fileName);
int		saveCompanyDataToFile(const Company* pComp, FILE* fp);
int		saveCompressCompanyDataToFile(const Company* pComp, FILE* fp);
int		loadCompanyFromFile(Company* pComp, const AirportManager* pManager, const char* fileName);
int		loadCompanyDataToFile(Company* pComp, const AirportManager* pManager, FILE* fp);
int		loadCompressCompanyDataToFile(Company* pComp, const AirportManager* pManager, FILE* fp);
void	sortFlight(Company* pComp);
void	findFlight(const Company* pComp);
eSortOption showSortMenu();

void	freeCompany(Company* pComp);

#endif

