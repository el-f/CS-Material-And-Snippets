#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* doF321(void *n1) {
	int n = *(int*) n1;
	int *k = malloc(sizeof(int));
	*k = 0;
	while (1) {
		if (n <= 1) {
			printf("For n1 = %d:\tk = %d\n", *(int*) n1, *k);
			pthread_exit((void*) k);
		}
		*k += 1;
		if (n % 2 == 0)
			n /= 2;
		else
			n = 3 * n + 1;
	}
}

void q3(int arr[], int size) {
	pthread_t threads[size];
	int *results[size];

	for (int i = 0; i < size; i++) {
		if (pthread_create(&threads[i], NULL, doF321, (void*) &arr[i])) {
			perror("pthread_create error!\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < size; i++) {
		if (pthread_join(threads[i], (void**) &(results[i]))) {
			perror("pthread_join error!\n");
			exit(EXIT_FAILURE);
		}
		printf("k = %d\n", *results[i]);
	}

	puts("\nResults:");
	for (int i = 0; i < size; i++) {
		printf("Thread id: %lu\tk: %d\n", threads[i], *results[i]);
		free(results[i]);
	}
}

int main() {
	int arr[] = { 17, 65, 34, 91, 92, 93, 33, 16, 22, 75 };
	q3(arr, 10);
}
