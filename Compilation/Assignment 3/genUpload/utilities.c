#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utilities.h"

/* implementation of a stack of ints */ 

void initStack (intStack *s)
{
    s->n = 0;	
}
void push(intStack *s, int value) 
{
    if (s->n >= STACK_SIZE) {
        fprintf(stderr, "stack overflow\n");
        exit(1);
	}
    s->stack[s->n++] = value;
}

int pop(intStack *s) 
{
    assert(s->n > 0); 
    return s->stack[--s->n];
}

int isEmpty(intStack *s)
{
	return s->n == 0;
}

int peek(intStack *s)
{
    assert(s->n > 0); 
	return s->stack[s->n -1];
}


