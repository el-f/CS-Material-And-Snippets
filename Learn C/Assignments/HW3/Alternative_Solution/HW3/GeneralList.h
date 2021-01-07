/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_

//#include "Airport.h"


/*** Definitions ***/
//typedef Airport* DATA;
typedef void* DATA;

typedef enum { False, True } BOOL;	// a boolean type


// Node
typedef struct node
{
	DATA			key;
	struct node*	next;
}NODE;


// List
typedef struct 
{
	NODE head;
}LIST;


/*** Function prototypes ***/
// create new list
BOOL L_init(LIST* pList);					

// add new node after *pNode
NODE* L_insert(NODE* pNode, DATA Value);	

// erase node after *pNode
BOOL L_delete(NODE* pNode, void freeFunc(void*));

// return a pointer to the node 
NODE* L_find(NODE* pNode, DATA Value,int compare(const void*, const void*));

// free list memory
BOOL L_free(LIST* pList, void freeFunc(void*));

// print the list content
int L_print(const LIST* pList,void (*print)(const void* ));
#endif
