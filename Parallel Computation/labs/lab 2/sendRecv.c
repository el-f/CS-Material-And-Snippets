#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int x, y;
    int my_rank;            /* rank of process */
    int p;                /* number of processes */
    MPI_Status status;    /* return status for receive */

    /* start up MPI */
    MPI_Init(&argc, &argv);

    /* find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* find out number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (p != 2) { // Handle invalid input p
        printf("Error! p=%d, please run with p=2\n", p);
        MPI_Abort(MPI_COMM_WORLD, __LINE__); // __LINE__ = current line number
    }

    if (my_rank == 0) {
        x = 7;
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        printf("The new value of x = %d\n", x);
    } else {
        MPI_Recv(&y, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        y *= 3;
        MPI_Send(&y, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    /* shut down MPI */
    MPI_Finalize();


    return 0;
}