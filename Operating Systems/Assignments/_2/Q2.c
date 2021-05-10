#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "circular_buffer.h"

#define TUPLE_LEN 3

void write_to_buffer(circular_buffer *buffer, int *tuple) {
	if (!buffer->lock && !buffer->isFull) {
		for (int i = 0; i < TUPLE_LEN; i++) {
			push(buffer, tuple[i]);
		}
		buffer->lock = true;
	}
}

void read_from_buffer(circular_buffer *buffer, int *tuple) {
	if (!isEmpty(buffer)) {
		for (int i = 0; i < TUPLE_LEN; i++) {
			tuple[i] = pop(buffer);
		}
	}
	buffer->lock = false;
}

void q2(int arr[], int size) {
	circular_buffer *parent_to_child_buf = mmap(
	NULL, sizeof(circular_buffer),
	PROT_READ | PROT_WRITE,
	MAP_SHARED | MAP_ANONYMOUS, 0, 0);
	if (parent_to_child_buf == MAP_FAILED) {
		perror("mmap error! (parent_to_child_buf)\n");
		exit(EXIT_FAILURE);
	}

	circular_buffer *child_to_partent_buf = mmap(
	NULL, sizeof(circular_buffer),
	PROT_READ | PROT_WRITE,
	MAP_SHARED | MAP_ANONYMOUS, 0, 0);
	if (child_to_partent_buf == MAP_FAILED) {
		perror("mmap error! (child_to_partent_buf)\n");
		exit(EXIT_FAILURE);
	}

	int tuple[TUPLE_LEN];

	pid_t pid = fork();
	if (pid == -1) {
		perror("Fork Error!\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) { // child process
		while (1) {
			if (parent_to_child_buf->lock) {
				read_from_buffer(parent_to_child_buf, tuple);
				if (tuple[0] == 0)	// flag to terminate
					break;

				while (tuple[1] % 2 == 0) {
					tuple[1] /= 2;
					tuple[2] += 1;
				}
				write_to_buffer(child_to_partent_buf, tuple);
			}
		}
	} else { // parent process
		for (int i = 0; i < size; i++) {
			tuple[0] = arr[i];
			tuple[1] = arr[i];
			tuple[2] = 0;
			write_to_buffer(parent_to_child_buf, tuple);

			while (1) {
				if (child_to_partent_buf->lock) {
					read_from_buffer(child_to_partent_buf, tuple);
					if (tuple[1] == 1) {
						printf("%d, %d, %d\n\n", tuple[0], tuple[1], tuple[2]);
						break;
					}
					if (tuple[1] % 2) {
						tuple[1] = tuple[1] * 3 + 1;
						tuple[2] += 1;
						printf("%d, %d, %d\n", tuple[0], tuple[1], tuple[2]);
						write_to_buffer(parent_to_child_buf, tuple);
						sleep(1);
					}

				}
			}
		}
		tuple[0] = tuple[1] = tuple[2] = 0;				//
		write_to_buffer(parent_to_child_buf, tuple);	//	terminate child
		wait(NULL);										//
	}
	if (munmap(parent_to_child_buf, sizeof(circular_buffer))
			|| munmap(child_to_partent_buf, sizeof(circular_buffer))) {
		perror("munmap error!\n");
		exit(EXIT_FAILURE);
	}
}

int main() {
	int arr[] = { 17, 65, 34, 91, 92, 93, 33, 16, 22, 75 };
	q2(arr, 10);
}
