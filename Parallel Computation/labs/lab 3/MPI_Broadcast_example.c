#include "mpi.h"
#include <stdio.h>
#include <string.h>

#define SIZE 10

int main(int argc, char *argv[])
{
    int myid, numprocs;
    char buffer[SIZE] = {'\0'};

    int errorCode = MPI_ERR_COMM;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    // Exit if launced only one process
    if (numprocs == 1) MPI_Abort(MPI_COMM_WORLD, errorCode);

    // Initialize the send buffer in root process
    if (myid == 0) strcpy(buffer, "afeka");
    printf("before bcast myid = %d, buffer = %s\n", myid, buffer);

    // Perform the broadcast
    MPI_Bcast(buffer, SIZE, MPI_CHAR, 0, MPI_COMM_WORLD);
    printf("after bcast myid = %d, buffer = %s\n", myid, buffer);


    MPI_Finalize();
    return 0;
}
