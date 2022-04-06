#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int myid, numprocs;
    int color, newRank;
    MPI_Comm newComm;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    color = myid % 2;

    MPI_Comm_split(MPI_COMM_WORLD, color, 0, &newComm);
    MPI_Comm_rank(newComm, &newRank);
    printf("myid = %d, color = %d     newRank = %d\n", myid, color, newRank);

    MPI_Finalize();

}


