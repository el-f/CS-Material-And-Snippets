#ifndef __CUSTOMER__
#define __CUSTOMER__

#include <stdio.h>


struct Super;

struct Customer
{
	char name[10];
	struct Super* pSup;
};

typedef struct Customer Customer_t;

void printCustomer(const Customer_t* pCust);

#endif
