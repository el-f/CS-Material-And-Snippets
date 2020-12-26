#pragma once

#include "list.h"

void createListFromArr(LIST *pLst, const int *arr, int size);

int findMax(NODE *pN);

void removeDuplicates(NODE *pN);

void insertToNum(LIST *pList, int num);

void removeValFromList(LIST *pList, int val);

void removeNMaxFromList(LIST *pList, int num);

NODE *findBeforeMax(LIST *pList);

