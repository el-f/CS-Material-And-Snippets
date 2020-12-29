#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "listGen.h"
#include "Person.h"

#define N 5

void Q1();
void Q2();


int main()
{
	Q1();
	Q2();
	system("pause");
}

void Q1()
{
	LIST	lst;
	int i;
	NODE* pNode;

	Person arr[N];
	for(i = 0; i < N; i++)
	{
		initPerson(&arr[i]);
	}

	printf("The persons in array\n");
	for(int i = 0; i < N; i++)
	{
		showPerson(&arr[i]);
	}

	// Initialization
	L_init(&lst);

	//Add to list 1 after the other
	pNode = &lst.head;
	for(i = 0; i < N; i++)
		pNode = L_insert(pNode, &arr[i]);

	printf("\nThe persons in list");
	//Add code here to print the list of persons
	L_print(&lst,showPerson);

	L_delete(&lst.head,NULL);
	printf("The persons in list after delete the first one");
	//Add code here to print the list of persons
	L_print(&lst,showPerson);
	
	printf("Enter id to find\n");
	int id;
	scanf("%d",&id);
	//Add code here to search for person with id
	Person temp;
	temp.id = id;
	pNode =  L_find(lst.head.next,&temp,comparePersonById);
	if(pNode)
	{
		printf("Person found\n");
		showPerson(pNode->key);
	} else
		printf("Person not found\n");


	// Finish work
	L_free(&lst,NULL);
}


void Q2()
{
	LIST	lst;
	int		count;
	NODE*	pNode;


//// Initialization
	L_init(&lst);

	printf("Please enter person count\n");
	scanf("%d", &count);

	Person* p;
	pNode = &lst.head;
	for (int i = 0; i < count; i++)
	{
		p = (Person*)malloc(sizeof(Person));
		if (!p)
			return;
		initPerson(p);
		pNode = L_insert(pNode, p);
	}

	printf("\nThe persons in list");
	L_print(&lst, showPerson);


	printf("Enter id to find\n");
	int id;
	scanf("%d", &id);
	//Add code here to search for person with id
	Person tempPerson = { id,"" };
	pNode = L_find(lst.head.next, &tempPerson, comparePersonById);
	if (pNode)
	{
		printf("Person found\n");
		showPerson(pNode->key);
	}
	else
		printf("Person not found\n");


	// Finish work
	L_free(&lst, freePerson);
}

