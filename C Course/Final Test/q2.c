#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q2.h"


void Q2() {
    LIST lst;

    /*-------- INIT LIST --------*/
    initListOfOrder(&lst);

    /*-------- PRINT ALL --------*/
    printf("\n ------- The list ------------\n");
    printAllOrders(&lst);

    /*-------- DELETE LAST --------*/
    /*
     * We can just look at the last barcode and
     * get its order with find...BUT I don't think that's what you meant + it feels cheap.
     * so...:
     * finding last order without explicitly entering the last order as input:
     */
    NODE *pNode = &lst.head;
    while (pNode->next != NULL) pNode = pNode->next;
    deleteOrder(pNode->key, &lst);
    printf("\n ------- The list after delete last ------------\n");
    printAllOrders(&lst);

    /*-------- SEARCH --------*/
    Order *found = searchOrder(&lst);
    if (found == NULL) {
        puts("Order with this barcode not found!");
    } else {
        puts("Order found:");
        printOrder(found);
    }
}

void printOrder(const void *order) {
    Order *o = (Order *) order;
    printf("Order: %s barcode: %s price: %.2f\n", o->name, o->barcode, o->price);
}

int compareOrders(const void *order1, const void *order2) {
    Order *o1 = (Order *) order1;
    Order *o2 = (Order *) order2;
    return strcmp(o1->barcode, o2->barcode);
}

Order *searchOrder(const LIST *list) {
    Order dummy;
    puts("Enter barcode (max 9 chars) to search");
    scanf("%s", dummy.barcode);
    NODE *found = L_find(list->head.next, &dummy, compareOrders);
    return found != NULL ? found->key : NULL;
}

void printAllOrders(const LIST *list) {
    if (list->head.next == NULL) {
        puts("The list is empty, nothing to print...");
        return;
    }
    L_print(list, printOrder);
}

void freeOrder(void *order) {
    Order *o = (Order *) order;
    free(o->name);
    free(o);
}

/*
 * Assuming we delete by order this is the way...
 * there are other ways (by index, by node, by barcode, etc...),
 * even more efficient (by node saves us the while loop),
 * but since it's not written how we implement it this is pretty
 * much the most straightforward way to implement a delete function IMO.
 */
int deleteOrder(Order *order, LIST *list) {
    NODE *pNode = &list->head;
    while (pNode->next != NULL) {
        if (compareOrders(pNode->next->key, order) == 0) break;
        pNode = pNode->next;
    }
    if (pNode == NULL) {
        puts("No such order in the list!");
        return 0;
    }
    return L_delete(pNode, freeOrder);
}

int initListOfOrder(LIST *plst) {
    L_init(plst);
    int count;
    Order *pTemp;
    NODE *pN = &plst->head;

    printf("How many orders in list?\n");
    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        pTemp = (Order *) malloc(sizeof(Order));
        if (!pTemp)
            return 0;
        initOrderFromUser(pTemp);
        pN = L_insert(pN, pTemp);
    }

    return 1;
}


int initOrderFromUser(Order *pOrder) {
    printf("Please enter order name, barcode (%d chars) and price\n", LEN);
    char temp[255];
    scanf("%s %s %f", temp, pOrder->barcode, &pOrder->price);
    pOrder->name = _strdup(temp);
    if (!pOrder->name)
        return 0;
    return 1;
}