/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_

#include <stdbool.h>


/*** Definitions ***/

// Node
typedef struct node {
    void *key;
    struct node *next;
} NODE;

// List
typedef struct {
    NODE head;
} LIST;


/*** Function prototypes ***/

// create new list
bool L_init(LIST *pList);

// add new node after *pNode
NODE *L_insert(NODE *pNode, void *Value);

// erase node after *pNode
bool L_delete(NODE *pNode, void (*freeFunc)(void *));

// return a pointer to the node
NODE *L_find(NODE *pNode, void *Value, int(*compare)(const void *, const void *));

// free list memory
bool L_free(LIST *pList, void (*freeFunc)(void *));

// print the list content
int L_print(const LIST *pList, void(*print)(const void *));

#endif
