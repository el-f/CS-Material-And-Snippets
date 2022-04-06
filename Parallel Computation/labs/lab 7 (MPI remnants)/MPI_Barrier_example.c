#include "mpi.h"
#include <stdio.h>


void heavyTask(double sec) {
    double t = MPI_Wtime();

    // Loop till sec seconds will pass
    while (MPI_Wtime() - t < sec);
}

int main(int argc, char *argv[]) {
    int rank, numprocs;
    double t1, t2;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Check that there is exactly two proceeses
    if (numprocs < 2)
        MPI_Abort(MPI_COMM_WORLD, 0);


    t1 = MPI_Wtime();
    if (rank == 1)
        heavyTask(2);

    MPI_Barrier(MPI_COMM_WORLD);
    t2 = MPI_Wtime();

    printf("myrank = %d time = %e\n", rank, t2 - t1);
    MPI_Finalize();
    return 0;
}


