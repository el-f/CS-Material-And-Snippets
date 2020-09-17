#include <stdio.h>
#include <stdlib.h>

/*
Positives:

* Dynamic:
            - no need to know size ahead of time
* Optimized:
            - easy to insert/extract in the middle
            - no "holes"
            - no need to push to insert or extract
* Flexible in terms of memory:
            - doesn't have to be continous
            - not declared all at once

*/

/*
Negatives:

* Takes more memory:
                    - every value needs a pointer to the next
* No direct access to values in the middle:
                    - exploring the list only through subsequent pointers
* Code complexity:
                    - possible runtime failours
                    - bad readability
                    - possbile memory loss if forgeting to free unused vals

*/

/*
Implementations Runtime Comparisons:

<Operation>     <Array/List>        <Linked List>       <Doubly Linked List>
init                O(1)                O(1)                O(1)
isEmpty()           O(1)                O(1)                O(1)
isFull()            O(1)                N/A                 N/A
findNext()          O(1)                O(1)                O(1)
findPrev()          O(1)                O(n)                O(1)
insertFirst()       O(n)                O(1)                O(1)
insertLast()        O(1)                O(1)                O(1)
insertAt(p)         O(n)                O(1)                O(1)
insertAfter(p)      O(n)                O(n)                O(n)
deleteFirst()       O(n)                O(1)                O(1)
deleteLast()        O(1)                O(n)                O(1)
deleteValue(x)      O(n)                O(n)                O(n)
deleteAt(p)         O(n)                O(n)                O(1)
*/

typedef struct listnode
{
    int data;
    struct listnode *next;
} Node;

int main(int argc, char const *argv[])
{

    Node head;
    head.data = 6;
    printf("%d\n", head.data);

    Node *p;
    p = &head;
    (*p).data = 7;
    printf("%d\n", head.data);

    p->data = 8; //same as (*p).data = 8
    printf("%d\n", head.data);

    p->next = p;
    printf("%d\n", head.data);
    printf("%d\n", head.next);

    Node *q = (Node *)malloc(sizeof(Node));
    q->data = 77;
    q->next = p;
    printf("%d\n", head.data);
    printf("%d\n", head.next->data);

    Node rina;
    rina.data = 999;
    Node wow;
    wow.data = -123;

    head.next = &rina;
    rina.next = &wow;

    printf("%d\n", head.data);
    printf("%d\n", head.next->data);
    printf("%d\n", head.next->next->data);

    Node *head1;
    Node *head2;
    Node *head3;
    Node *p = head3;
    Node *p1 = head1->next;
    Node *p2 = head2->next;

    //concating a list to the end of another list
    Node *p = head3;
    while (p1 != NULL)
    {
        p1->next = (Node *)malloc(sizeof(Node));
        p = p->next;
        p->data = p1->data;
        p1 = p1->next;
    }
    while (p2 != NULL)
    {
        p2->next = (Node *)malloc(sizeof(Node));
        p = p->next;
        p->data = p2->data;
        p2 = p2->next;
    }
    p->next = NULL; //ending the list

    return 0;
}

int insertAfter(int precedingVal, int newVal, Node head)
{
    Node *p;
    p = head.next;
    while (p != NULL && p->data != precedingVal)
    {
        p = p->next;
    }
    if (p->data == precedingVal)
    {
        p->next = (Node *)malloc(sizeof(Node));
        p->next->data = newVal;
        p->next->next = NULL;
        return 1;
    }
    else
        return 0;
}

int deleteAfter(int precedingVal, int newVal, Node head)
{
    Node *p;
    p = &head;
    while (p->next != NULL && p->next->data != precedingVal)
    {
        p = p->next;
    }
    if (p->data == precedingVal)
    {
        Node *q;
        q = p->next;
        p->next = q->next;
        free(q);

        return 1;
    }
    else
        return 0;
}

void reverseTheList(Node *head)
{
    /*
        First Solution:
        Getting Last item n times

        while(!list.isEmpty())
        {
            newList.insertFirst(list.getLast()); 
        }

        Runtime = O(n^2)
    
    */

    /*
        Second Solution:
        Using Stack

        list = ...magic(head)...
        stack = ...magic...

        while(!isEmpty(list))
        {
            stack.push(deleteFirst(list));
        }
        while(!isEmpty(stack))
        {
            list.insertLast(pop(stack))
        }

        runtime = O(n)
    */

    /*
        Third Solution:
        Going through the list and moving each node to be first.
        Using prev and current pointers

        prev = head->next;
        curr = head->next->next;

        while(curr != NULL)
        {
            prev->next = curr->next;
            curr->next = head->next;
            head->next = curr;
            curr = prev->next;
        }


        Runtime = O(n)

    */

    /*
        Fourth Solution:
        Recursive

        Node* listReverse(head)
        {
            if(head->next == NULL)
                return head;

            temp = listReverse(head->next);
            head->next->next = head;
            head->next = NULL;
            return temp;
        }

    */
}
