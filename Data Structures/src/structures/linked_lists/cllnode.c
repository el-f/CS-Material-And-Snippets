#include <stdio.h>
#include <stdlib.h>

//Circular linked list
typedef struct cllnode {
    int data;
    struct cllnode *next;
} CNode;

int main(int argc, char const *argv[]) {
    CNode *head;
    CNode *p = head->next;

    //count nodes in the circular linked list
    int numOfNodesInCLL;
    while (p != head->next) {
        numOfNodesInCLL++;
        p = p->next;
    }

    CNode *head1;
    CNode *head2;

    //concating the second list the to first
    //find end of first list
    CNode *end1;
    while (end1->next != head1->next) {
        end1 = end1->next;
    }
    /*
    last node in first list will point to the start of
    the second list instead of the start of the first list
    */
    end1->next = head2->next;

    //find end of second list
    CNode *end2;
    while (end2->next != head2->next) {
        end2 = end2->next;
    }
    //set end of second list to start of first list
    //now we have one circular linked list
    end2->next = head1->next;

    //creating a new list "by hand" from the two lists, item by item.
    CNode *head3;
    CNode *p = head3;
    CNode *p1 = head1->next;
    CNode *p2 = head2->next;
    while (p1 != NULL) {
        insertLast(head3, p1->data);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        insertLast(head3, p2->data);
        p2 = p2->next;
    }

    //when we already have ends of lists just do this
    end1->next = head2->next;
    end2->next = head1->next;
    free(head2);

    return 0;
}

void insertLast(CNode *head, int data) {
    //magic...
}
