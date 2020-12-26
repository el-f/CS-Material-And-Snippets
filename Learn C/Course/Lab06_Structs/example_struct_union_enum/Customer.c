#include <stdio.h>

#include "Super.h"
#include "Customer.h"


void printCustomer(const Customer_t* pCust)
{
	printf("Customer:%s\t",pCust->name);
	if(pCust->pSup == NULL)
		printf("Not in super\n");
	else
		printf("In Super %s\n",pCust->pSup->name);
}

