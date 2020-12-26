#include <stdio.h>
#include <string.h>
#include "Customer.h"
#include "Super.h"

void Q1();
void Q2();

union student
{
	char name[20];
	char subject[20];
	float percentage;
};



int main()
{
	Q1();
	Q2();
}

void Q1()
{
	union student record1;
	union student record2;

	// assigning values to record1 union variable
	strcpy(record1.name, "Raju");
	strcpy(record1.subject, "Maths");
	record1.percentage = 86.50;

	printf("Union record1 values example\n");
	printf(" Name       : %s \n", record1.name);
	printf(" Subject    : %s \n", record1.subject);
	printf(" Percentage : %f \n\n", record1.percentage);

	// assigning values to record2 union variable
	printf("Union record2 values example\n");
	strcpy(record2.name, "Mani");
	printf(" Name       : %s \n", record2.name);

	strcpy(record2.subject, "Physics");
	printf(" Subject    : %s \n", record2.subject);

	record2.percentage = 99.50;
	printf(" Percentage : %f \n", record2.percentage);
}

void Q2()
{
	printf("\n --------- Q2 ------------\n");

	Customer_t cust;
	Super_t sup;

	strcpy(cust.name,"Levi");
	cust.pSup = NULL;

	strcpy(sup.name,"Mega");
	sup.pCust = NULL; //No customer!! 
	sup.type = eClothes;

	printCustomer(&cust);
	printSuper(&sup);

	//enterSuper
	printf("\nGot into Super\n");
	cust.pSup =  &sup;
	sup.pCust = &cust;

	printCustomer(&cust);
	printSuper(&sup);




}
