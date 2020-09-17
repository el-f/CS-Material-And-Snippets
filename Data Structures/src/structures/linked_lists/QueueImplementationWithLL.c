#include <stdio.h>
#include <stdlib.h>

typedef struct listnode
{
    int data;
    struct listnode *next;
} Node;

/*
Queue Implementation With Linked List
Enqueue, Dequeue, Front - O(1) <=> insert, delete, find
*/

void Enqueue(Node *tail, int x)
{
    // insertLast(tail, x);

    //create a new cell from the data x and insert
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = x;
    temp->next = NULL;
    tail->next = temp;
    tail = temp;
    
}

int Front(Node *head)
{
    return findFirst(head);
}

int Dequeue(Node *head)
{
    int temp = findFirst(head);
    deleteFirst(head);
    return temp;
}

int findFirst(Node *head)
{
    return head->next->data;
}

void insertLast(Node *head, int x)
{
    //magic
}

void deleteFirst(Node *head)
{
    head->next = head->next->next;
}
