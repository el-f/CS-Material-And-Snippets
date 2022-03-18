#include "mpi.h"
#include <stdio.h>


int main(int argc, char **argv) {
    int rank, size;
    int data[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        printf("launch 4 processes only\n");
        MPI_Abort(MPI_COMM_WORLD, 0);
    }

    if (rank == 0) {
        int original[] = {1, 2, 3, 4, 5, 6, 7, 8};
        // Scatter the array - 2 integers for each process
        MPI_Scatter(original, 2, MPI_INT, data, 2, MPI_INT, 0, MPI_COMM_WORLD);
    } else
        MPI_Scatter(NULL, 0, MPI_INT, data, 2, MPI_INT, 0, MPI_COMM_WORLD);

    printf("rank = %d data = [%d, %d]\n", rank, data[0], data[1]);


    MPI_Finalize();
    return 0;
}

