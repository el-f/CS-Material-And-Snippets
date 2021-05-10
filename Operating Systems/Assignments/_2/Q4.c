#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

int doF321(int n1) {
	int n = n1;
	int k = 0;
	while (1) {
		if (n <= 1)
			return k;
		k += 1;
		if (n % 2 == 0)
			n /= 2;
		else
			n = 3 * n + 1;
	}
}

void q4(int arr[], int size) {
	int *results = mmap(
	NULL, sizeof(int) * size,
	PROT_READ | PROT_WRITE,
	MAP_SHARED | MAP_ANONYMOUS, 0, 0);
	if (results == MAP_FAILED) {
		perror("mmap error!\n");
		exit(EXIT_FAILURE);
	}

	pid_t pids[size];
	for (int i = 0; i < size; i++) {
		int n1 = arr[i];
		if ((pids[i] = fork()) == -1) {
			perror("Fork error!\n");
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0) { // child process
			results[i] = doF321(n1);
			printf("For n1 = %d:\tk = %d\n", n1, results[i]);
			exit(EXIT_SUCCESS);
		}
	}
	for (int i = 0; i < size; i++) {
		wait(NULL);	// wait for all children
	}
	puts("\nResults:");
	for (int i = 0; i < size; i++) {
		printf("process #%d:\t%d\n", i + 1, results[i]);
	}

	if (munmap(results, sizeof(int) * size)) {
		perror("munmap error!\n");
		exit(EXIT_FAILURE);
	}
}

int main() {
	int arr[] = { 17, 65, 34, 91, 92, 93, 33, 16, 22, 75 };
	q4(arr, 10);
}

