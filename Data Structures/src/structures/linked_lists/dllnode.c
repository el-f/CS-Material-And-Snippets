#include <stdio.h>
#include <stdlib.h>

//Doubly linked list
typedef struct dllnode
{
    int data;
    struct dllnode *next;
    struct dllnode *prev;
} DNode;

int main(int argc, char const *argv[])
{
    DNode *p; //node at i
    DNode *q; //node at i+1
    q = p->next;

    //create new node to insert between p and q
    DNode *newNode = (DNode *)malloc(sizeof(DNode));
    newNode->data = 1337;

    //insert the new node between p and q
    p->next = newNode;
    q->prev = newNode;
    newNode->next = q;
    newNode->prev = p;

    //deleting the new node
    newNode->next->prev = newNode->prev;
    newNode->prev->next = newNode->next;
    free(newNode);

    //concating a list to the end of another list
    DNode *head1;
    DNode *tail1;
    DNode *head2;
    DNode *tail2;

    tail1->next = head2->next;
    head2->next->prev = tail1;
    tail1 = tail2;

    return 0;
}
