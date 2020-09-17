#include <stdio.h>
#include <stdlib.h>

/*
excersice part 1
*/

typedef struct listnode
{
    int data;
    struct listnode *next;
} Node;

//Q1
int replaceFirstTwoDatas(Node head)
{
    if (head.next == NULL)
        return 1;
    else
    {
        int temp = head.data;
        head.data = head.next->data;
        head.next->data = temp;
        return 0;
    }
}

//Q2
int replaceFirstTwoNodes(Node *head)
{
    if (head->next == NULL || head->next->next == NULL)
        return 1;
    else
    {
        int thirdNode = head->next->next;
        head->next->next = head;
        int secondNode = head->next;
        head->next = thirdNode;
        head = secondNode;

        return 0;
    }
}

//Q3
int replaceTwoNodesAfterPointer(Node *ptr)
{
    if (ptr->next == NULL || ptr->next->next == NULL)
        return 1;
    else
    {
        int fourthNode = ptr->next->next->next;
        ptr->next->next->next = ptr->next;

        int thirdNode = ptr->next->next;
        ptr->next->next = fourthNode;

        ptr->next = thirdNode;

        return 0;
    }
}

//Q4
int replacePointedNodeWithNext(Node *ptr, Node *head)
{
    if (ptr == NULL || ptr->next == NULL)
        return 1;
    else
    {
        Node *p = head;
        //get p until p points to one cell before ptr
        while (p != NULL && p->next != ptr)
        {
            p = p->next;
        }
        p->next = ptr->next;

        ptr->next = ptr->next->next;

        ptr->next->next = ptr;

        return 0;
    }
}

//Q5
int findMax(Node *head)
{
    int max = 0;
    while (head != NULL)
    {
        if (head->data > max)
            max = head->data;
        head = head->next;
    }
    return max;
}

//Q6
int findMaxPointer(Node *head)
{
    int max;
    int maxPointer;
    while (head != NULL)
    {
        if (head->data > max)
        {
            max = head->data;
            maxPointer = head;
        }
        head = head->next;
    }
    return maxPointer;
}

//Q7

int findMaxRec(Node *head)
{
    if (head->next == NULL)
        return head->data;
    int maxInNextSteps = findMaxRec(head->next);
    if (head->data > maxInNextSteps)
        return head->data;
    else
        return maxInNextSteps;
}

int findMaxPointerRec(Node *head)
{
    if (head->next == NULL)
        return head;
    Node *maxPointerInNextSteps = findMaxRec(head->next);
    if (head->data > maxPointerInNextSteps->data)
        return head;
    else
        return maxPointerInNextSteps;
}