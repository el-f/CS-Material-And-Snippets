#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    int rank, size, i, sum;
    int *array;
    int data[3];
    int result[4];
    int totalSum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        printf("launch 4 processes only\n");
        MPI_Abort(MPI_COMM_WORLD, 0);
    }

    if (rank == 2) {
        array = (int *) malloc(12 * sizeof(int));
        for (i = 0; i < 12; i++)
            array[i] = i;
    }

    MPI_Scatter(array, 3, MPI_INT, data, 3, MPI_INT, 2, MPI_COMM_WORLD);

    sum = 0;
    for (i = 0; i < 3; i++)
        sum += data[i];

    MPI_Gather(&sum, 1, MPI_INT, result, 1, MPI_INT, 2, MPI_COMM_WORLD);


    if (rank == 2) {
        totalSum = 0;
        for (i = 0; i < size; i++)
            totalSum += result[i];
    }

    MPI_Bcast(&totalSum, 1, MPI_INT, 2, MPI_COMM_WORLD);

    printf("rank = %d totalSum = %d\n", rank, totalSum);


    MPI_Finalize();
    return 0;
}
