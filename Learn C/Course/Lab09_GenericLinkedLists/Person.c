#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Person.h"


void initPerson(Person* pPer)
{
	printf("Please enter person name and  id\n");
	scanf("%s %d",pPer->name, &pPer->id);
}

void	showPerson(const void* p)
{
	const Person* pPer = (const Person*)p;
	printf("Person: %s id %d\n",pPer->name, pPer->id);

}

int	comparePersonById(const void* p1, const void* p2)
{
	const Person* pS1 = (const Person*)p1;
	const Person* pS2 = (const Person*)p2;
	return pS1->id-pS2->id;
}

void	freePerson(void* p)
{
	free(p);
}