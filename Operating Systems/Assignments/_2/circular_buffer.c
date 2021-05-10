#include "circular_buffer.h"

bool isEmpty(circular_buffer *buffer) {
	return (buffer->head == buffer->tail) && !buffer->isFull;
}

int pop(circular_buffer *buffer) {
	int item = buffer->data[buffer->tail];
	buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;
	buffer->isFull = false;

	return item;
}

void push(circular_buffer *buffer, int data) {
	buffer->data[buffer->head] = data;
	buffer->head = (buffer->head + 1) % BUFFER_SIZE;
	buffer->isFull = buffer->head == buffer->tail;
}
