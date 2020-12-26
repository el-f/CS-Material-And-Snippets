#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "listGen.h"
#include "Person.h"


int main()
{
	LIST	lst;
	int i;
	NODE* ptr1;

	Person arr[5];
	for(i = 0; i < 5; i++)
	{
		initPerson(&arr[i]);
	}

	printf("The persons in array\n");
	for(int i = 0; i < 5; i++)
	{
		showPerson(&arr[i]);
	}

	// Initialization
	L_init(&lst);

	//Add to list 1 after the other
	ptr1 = &lst.head;
	for(i = 0; i < 5; i++)
		ptr1 = L_insert(ptr1, &arr[i]);

	printf("\nThe persons in list");
	//Add code here to print the list of persons
	//L_print(

	L_delete(&lst.head);
	printf("The persons in list after delete the first one");
	//Add code here to print the list of persons
	//L_print(

	printf("Enter id to find\n");
	int id;
	scanf("%d",&id);
	//Add code here to search for person with id

	//ptr1 =  L_find(
	//if(ptr1)
	//{
	//	
	//} else
	//	printf("Person not found\n");


	// Finish work
	L_free(&lst);
	system("pause");
}

