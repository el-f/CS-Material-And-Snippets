#include <stdio.h>
#include <stdlib.h>

typedef struct listnode
{
    int data;
    struct listnode *next;
} Node;

/*
Stack Implementation With Linked List
push, pop, top - O(1) <=> insert, delete, find
*/

void push(Node *head, int x)
{
    insertFirst(head, x);
}

int top(Node *head)
{
    return findFirst(head);
}

int pop(Node *head)
{
    int temp = top(head);
    deleteFirst(head);
    return temp;
}

int findFirst(Node *head)
{
    return head->data;
}

void insertFirst(Node *head, int x)
{
    //magic
}

void deleteFirst(Node *head)
{
    //magic
}
