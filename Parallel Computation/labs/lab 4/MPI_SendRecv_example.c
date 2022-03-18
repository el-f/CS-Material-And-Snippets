#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int myid, numprocs, left, right;
    int buffer[10], buffer2[10];
    int x, y;
    int dest;
    int errorCode = 999;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    // Check that there is exactly two proceeses
    if (numprocs != 2)
        MPI_Abort(MPI_COMM_WORLD, errorCode);

    // Define the rank of destination processes
    if (myid == 0)
        dest = 1;
    else
        dest = 0;

    // Send the its rank to the destination
    x = myid;

    MPI_Sendrecv(&x, 1, MPI_INT, dest, 0, &y, 1, MPI_INT, dest, 0, MPI_COMM_WORLD, &status);


    printf("myid = %d, x = %d,  y = %d\n", myid, x, y);

    MPI_Finalize();
    return 0;
}


