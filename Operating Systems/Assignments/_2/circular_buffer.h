#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#define BUFFER_SIZE 12

#include <stdio.h>
#include <stdbool.h>

typedef struct {
	int data[BUFFER_SIZE];
	int head;
	int tail;
	bool isFull;
	bool lock;
} circular_buffer;

bool isEmpty(circular_buffer *buffer);
void push(circular_buffer *buffer, int data);
int pop(circular_buffer *buffer);

#endif
