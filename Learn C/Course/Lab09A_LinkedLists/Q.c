#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "Q.h"


int findMax(NODE *pNode) {
    if (!pNode) return EMPTY;

    int max = pNode->key;
    pNode = pNode->next;
    while (pNode != NULL) {
        if (pNode->key > max) {
            max = pNode->key;
        }
        pNode = pNode->next;
    }

    return max;
}

void removeDuplicates(NODE *pNode) {
    if (!pNode) return;
    while (pNode->next != NULL) {
        if (pNode->key == pNode->next->key) {
            L_delete(pNode);
        } else {
            pNode = pNode->next;
        }
    }
}


void insertToNum(LIST *pList, int num) {
    NODE *node = pList->head.next;
    while (node != NULL) {
        node = L_insert(node, num - node->key);
        node = node->next;
    }
}

void removeValFromList(LIST *pList, int val) {
    if (!pList) return;

    NODE *pNode = &pList->head;
    while (pNode->next != NULL) {
        if (pNode->next->key == val) {
            L_delete(pNode);
        } else {
            pNode = pNode->next;
        }
    }

}

int compareNodes(const void *vn1, const void *vn2) {
    NODE **n1 = (NODE **) vn1;
    NODE **n2 = (NODE **) vn2;

    return (*n1)->key == (*n2)->key ? 0 : (*n1)->key > (*n2)->key ? 1 : -1;
}

void removeNMaxFromList(LIST *pList, int num) {
    if (!pList) return;

    int size = 0;
    NODE *pNode = pList->head.next;

    while (pNode != NULL) {
        size++;
        pNode = pNode->next;
    }
    NODE *maxes[size];

    pNode = pList->head.next;
    int i = 0;
    while (pNode != NULL) {
        maxes[i++] = pNode;
        pNode = pNode->next;
    }

    qsort(maxes, size, sizeof(NODE *), compareNodes);

    for (i = 0; i < num; i++) {
        removeValFromList(pList, maxes[--size]->key);
    }
}

void createListFromArr(LIST *pLst, const int *arr, int size) {
    NODE *pN = &pLst->head;
    for (int i = 0; i < size; i++)
        pN = L_insert(pN, arr[i]);
}
