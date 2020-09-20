#include <stdio.h>
#include <stdbool.h>

//************* Definitions *************//

typedef struct listnode
{
    int data;
    struct listnode *next;
} node;

node *createList(); // create a new circular list

bool isEmpty(); // check if the list is empty

void insertFirst(int num); // insert num at the beginning of the list

void insertAfter(node *p, int num); // insert a new node after a node p

void deleteNode(node *p); // delete the node that p points to

void PrintList(node *p); // print the list

//***************************************//

bool isOnlyNodeInList(node *p)
{
    return p->next == p;
}

node *getKthNode(node *p, int k)
{
    node *t = p;
    for (int i = 0; i < k; i++)
    {
        t = t->next;
    }
    return t;
}

void eliminateByK(int n, int k)
{
    //create list
    node *dummy = createList();
    node *p = dummy;
    for (int i = 1; i <= n; i++, p = p->next)
    {
        insertAfter(p, i);
    }

    p = getKthNode(dummy, k); //get dummy then jump k positions
    while (!isOnlyNodeInList(p))
    {
        printf("%d ", p->data);
        node *q = getKthNode(p, k); //backup next jump
        deleteNode(p);
        p = q;
    }
    printf("\nLeader: %d", p->data);
}
