#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define MAX   10

int main(int argc, char **argv) {
    int myid, numprocs;
    MPI_Status status;
    int data[MAX];
    int count;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);


    if (myid == 0) {
        MPI_Recv(data, MAX, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        printf("count = %d, tag = %d, source = %d\n", count, status.MPI_TAG, status.MPI_SOURCE);
    } else {
        int data[3] = {3, 5, 7};
        MPI_Send(data, 3, MPI_INT, 0, 45, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}

