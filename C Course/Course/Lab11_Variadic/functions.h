#ifndef __FUNCTIONS__
#define __FUNCTIONS__


float calcAverage(int num, ...);

char *combiningStrings(const char *str, ...);

void manipulateArray(const void *arr, int size, void(*func)(const void *arr, int length), ...);


void printArrInt(const void *arr, int size);

void printSumArrInt(const void *arr, int size);

void printMaxArrInt(const void *arr, int size);

#endif