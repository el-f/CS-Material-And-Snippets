#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include "listGen.h"


//////////////////////////////////////////
// Init
// Aim:		create new list
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
//////////////////////////////////////////
bool L_init(LIST *pList) {
    if (pList == NULL) return false;    // no list to initialize

    pList->head.next = NULL;
    return true;
}


/////////////////////////////////////////////////////////////////
// Insert
// Aim:		add new node
// Input:	pointer to the node BEFORE the place for the new one
//			a value to be stored in the new node
// Output:	pointer to the new node
/////////////////////////////////////////////////////////////////
NODE *L_insert(NODE *pNode, void *Value) {
    NODE *tmp;

    if (!pNode) return NULL;

    tmp = (NODE *) malloc(sizeof(NODE));    // new node

    if (tmp != NULL) {
        tmp->key = Value;
        tmp->next = pNode->next;
        pNode->next = tmp;
    }
    return tmp;
}


//////////////////////////////////////////////////////////////
// Delete
// Aim:		erase node
// Input:	pointer to the node BEFORE the node to be deleted 
// Output:	TRUE if succeeded
//////////////////////////////////////////////////////////////
bool L_delete(NODE *pNode, void (*freeFunc)(void *)) {
    NODE *tmp;

    if (!pNode || !(tmp = pNode->next)) return false;

    pNode->next = tmp->next;
    if (freeFunc != NULL)
        freeFunc(tmp->key);
    free(tmp);
    return true;
}


/////////////////////////////////////////////////////////
// Find
// Aim:		search for a value
// Input:	pointer to the node to start with 
//			a value to be found
// Output:	pointer to the node containing the Value
/////////////////////////////////////////////////////////
NODE *L_find(NODE *pNode, void *value, int(*compare)(const void *, const void *)) {
    NODE *temp = NULL;
    if (!pNode) return NULL;
    while (pNode != NULL) {
        if (compare(pNode->key, value) == 0) {
            temp = pNode;
            break;
        }
        pNode = pNode->next;
    }

    return temp;


}


////////////////////////////////////////////////
// Free (additional function)
// Aim:		free the list memory
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
////////////////////////////////////////////////
bool L_free(LIST *pList, void (*freeFunc)(void *)) {
    NODE *tmp;

    if (!pList) return false;
    tmp = &(pList->head);
    bool res = true;
    while (res) {
        res = L_delete(tmp, freeFunc);
    }

    return true;
}


////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content (assume the DATA is int)
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
int L_print(const LIST *pList, void(*print)(const void *)) {
    NODE *tmp;
    int c = 0;

    if (!pList) return 0;

    printf("\n");
    for (tmp = pList->head.next; tmp; tmp = tmp->next, c++)
        print(tmp->key);
    printf("\n");
    return c;
}
