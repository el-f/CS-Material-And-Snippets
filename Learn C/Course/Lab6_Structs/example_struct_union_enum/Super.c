#include <stdio.h>

#include "Customer.h"
#include "Super.h"


const char* ShopTypeStr[eNofTypes] = 
			{ "Food", "Clothes", "Shoes", "DrugStore"};


void printSuper(const Super_t* pSuper)
{
	printf("Super:%s\t Type:%s\t", pSuper->name, ShopTypeStr[pSuper->type]);
	if(pSuper->pCust == NULL)
		printf("No customer in super\n");
	else {
		printf("Customer %s In Super\n",pSuper->pCust->name);
	}
}
