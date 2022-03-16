#include "mpi.h"
#include <stdio.h>

#define MAX_PROCESSES 10
#define SIZE  4

int main(int argc, char **argv)
{
	int rank, size;
	int data[2];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (size != 4) {
		printf("launch 4 processes only\n");
		MPI_Abort(MPI_COMM_WORLD, 0);
	}

	// Local data to be gathered
	data[0] = rank;
	data[1] = rank + 1;

	if (rank != 0) {
		/* Scatter the big table to everybody's little table */
		MPI_Gather(data, 2, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
	} else {
		int result[2*SIZE];
		MPI_Gather(data, 2, MPI_INT, result, 2, MPI_INT, 0, MPI_COMM_WORLD);
		for (int i = 0;   i < SIZE;   i++)
			printf("%d %d\n", result[2*i], result[2*i + 1]);
	}

	MPI_Finalize();
	return 0;
}

