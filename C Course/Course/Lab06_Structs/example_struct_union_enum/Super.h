#ifndef __SUPER__
#define __SUPER__

#include <stdio.h>

struct Customer;

typedef enum {eFood, eClothes,eShoes,eDrugStore, eNofTypes} ShopType;
const char* ShopTypeStr[eNofTypes];

struct Super
{
	char		name[10];
	ShopType	type;
	struct Customer* pCust;
};

typedef struct Super Super_t;

void printSuper(const Super_t* pSuper);

#endif
