#ifndef __UTILITIES_H
#define __UTILITIES_H 1

/* interface to stack of ints */

enum stacksize { STACK_SIZE=100};

typedef struct intStack  {
	int stack[STACK_SIZE];
	int n; // number of elements in the stack;
} intStack;

void initStack (intStack *s);
void push(intStack *s, int value);
int pop(intStack *s); // returns element at top of stack and pops it
int isEmpty(intStack *s); // returns 1 if stack is empty otherwise 
                          // returns 0
int peek(intStack *s);    // returns int at top of stack 
                          // without popping it. Do not call peek()
						  // when stack is empty

#endif // not defined __UTILITIES_H 




