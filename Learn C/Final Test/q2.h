#pragma once

#include "GeneralList.h"

#define LEN 9

typedef struct {
    char *name;
    char barcode[LEN + 1];
    float price;
} Order;

void Q2();

int initListOfOrder(LIST *plst);

int initOrderFromUser(Order *pOrder);

void printOrder(const void *order);

Order *searchOrder(const LIST *list);

void printAllOrders(const LIST *list);

int deleteOrder(Order *order, LIST *list);

void freeOrder(void *order);

int compareOrders(const void *order1, const void *order2);