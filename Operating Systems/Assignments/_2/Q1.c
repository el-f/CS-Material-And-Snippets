#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define READ_INDEX	0
#define WRITE_INDEX	1
#define TUPLE_LEN   3

void q1(int arr[], int size) {
	int parent_to_child_pipe[2];
	int child_to_parent_pipe[2];

	if (pipe(parent_to_child_pipe) || pipe(child_to_parent_pipe)) {
		perror("\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();
	if (pid == -1) {
		perror("Fork Error!\n");
		exit(EXIT_FAILURE);
	}

	int tuple[TUPLE_LEN];
	int t_size = sizeof(int) * TUPLE_LEN;

	if (pid == 0) { // child process
		while (1) {
			int len = read(parent_to_child_pipe[READ_INDEX], &tuple, t_size);
			if (len <= 0) {
				perror("Pipe read error! (child)\n");
				exit(EXIT_FAILURE);
			}

			if (tuple[0] == 0) // flag to terminate
				break;

			while (tuple[1] % 2 == 0) {
				tuple[1] /= 2; // N
				tuple[2] += 1; // K
			}

			if (write(child_to_parent_pipe[WRITE_INDEX], &tuple, t_size)
					== -1) {
				perror("Pipe write error! (child)\n");
			}
		}
	} else { // parent process
		for (int i = 0; i < size; i++) {
			tuple[0] = arr[i];	// N1
			tuple[1] = arr[i];	// N
			tuple[2] = 0;		// K

			if (write(parent_to_child_pipe[WRITE_INDEX], &tuple, t_size)
					!= t_size) {
				perror("Pipe write error! (parent)\n");
				exit(EXIT_FAILURE);
			}

			while (1) {
				int len = read(child_to_parent_pipe[READ_INDEX], &tuple,
						t_size);
				if (len <= 0) {
					perror("Pipe read error! (parent)\n");
					exit(EXIT_FAILURE);
				}

				if (tuple[1] == 1) { // finished
					printf("%d, %d, %d\n\n", tuple[0], tuple[1], tuple[2]);
					break;
				}

				if (tuple[1] % 2) {
					tuple[1] = tuple[1] * 3 + 1;
					tuple[2] += 1;
					printf("%d, %d, %d\n", tuple[0], tuple[1], tuple[2]);
					if (write(parent_to_child_pipe[WRITE_INDEX], &tuple, t_size)
							!= t_size) {
						perror("Pipe write error! (parent)\n");
						exit(EXIT_FAILURE);
					}
					sleep(1);
				}
			}
		}
		tuple[0] = tuple[1] = tuple[2] = 0;								//
		if (write(parent_to_child_pipe[WRITE_INDEX], &tuple, t_size)	//
				!= t_size) {											//
			perror("Pipe write error! (parent)\n");						// terminate child
			exit(EXIT_FAILURE);											//
		}																//
		wait(NULL);														//

		for (int i = 0; i < 2; ++i) {
			close(child_to_parent_pipe[i]);
			close(parent_to_child_pipe[i]);
		}
	}

}

int main() {
	int arr[] = { 17, 65, 34, 91, 92, 93, 33, 16, 22, 75 };
	q1(arr, 10);
}
