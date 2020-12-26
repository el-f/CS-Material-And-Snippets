#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Person.h"


void initPerson(Person* pPer)
{
	printf("Please enter person name and  id\n");
	scanf("%s %d",pPer->name, &pPer->id);
}

