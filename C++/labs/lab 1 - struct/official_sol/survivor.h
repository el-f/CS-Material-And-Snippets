#ifndef __SURVIVOR_H
#define __SURVIVOR_H

typedef struct
{
	char name[20];
	int age;
} Survivor;

void initSurvivor(Survivor& s);
void printSurvivor(Survivor s);

#endif // __SURVIVOR_H