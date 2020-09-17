#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
excersice part 2
*/

//Linked List
typedef struct listnode
{
    int data;
    struct listnode *next;
} Node;

//Doubly linked list
typedef struct dllnode
{
    int data;
    struct dllnode *next;
    struct dllnode *prev;
} DNode;

//Q1

int countNode(Node *head)
{
    Node *p = head;
    int count = 0;
    while (p->next != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

int countNodeRecursive(Node *head, int count)
{
    if (head->next == NULL)
    {
        return 1;
    }
    return countNodeRecursive(head->next, count + 1);
}

//Q4
void deleteDuplicates(Node *head)
{
    Node *p = head;
    while (p->next != NULL)
    {
        if (p->data == p->next->data)
        {
            Node *q = p->next->next;
            p->next = p->next->next;
            free(q);
            p = p->next;
        }
    }
}

void deleteDuplicatesRecursive(Node *p)
{
    if (p == NULL)
    {
        return;
    }
    deleteDuplicatesRecursive(p->next);
    if (p->data == p->next->data)
    {
        Node *q = p->next;
        p->next = p->next->next;
        free(q);
    }
}

//Q5
void moveKNodes(Node *head, Node *tail, int k)
{
    tail->next = head->next;
    Node *p = head;
    for (int i = 0; i < k; i++)
    {
        if (p == NULL)
        {
            return 1; //returning error
        }

        p = p->next;
    }
    head->next = p->next;
    p->next = NULL;
    tail = p;
}

void moveKNodesCircular(Node *head, Node *tail, int k)
{
    for (int i = 0; i < k, head->next != NULL; i++)
    {
        tail = head->next;
        head->next = head->next->next;
    }
}

void moveKNodesDoubly(DNode *head, DNode *tail, int k)
{
    for (int i = 0; i < k, head->next != NULL; i++)
    {
        head->next->prev = tail;
        tail->next = head->next;
        head->next = head->next->next;
        head->next->prev = head;
        tail = tail->next;
        tail->next = NULL;
    }
}

//Q6
DNode *deCircAndGetTail(DNode *head, DNode *p)
{
    bool found = false;
    while (!found)
    {
        if (p->next == head->next)
        {
            p->next = NULL;
            found = true;
        }
        p = p->next;
    }
    return p;
}

DNode *deCircAndGetTail_DGANIT_SOLUTION(DNode *head, DNode *p)
{
    DNode *tail = p->prev;
    tail->next = NULL;
    p->prev = NULL;
    head->next = p;
    return tail;
}
