#include<mpi.h>
#include<stdio.h>
#include <stdlib.h>

#define ROWS  4
#define COLUMNS 3

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Comm comm;
    int dim[2], period[2], reorder;
    int coord[2], id;
    int row, column;
    int source, dest;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != ROWS * COLUMNS || argc != 3) {
        printf("Please run with 12 processes and two parametrs - row and column.\n");
        fflush(stdout);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Parameters from command line
    column = atoi(argv[1]);
    row = atoi(argv[2]);
    if (row > ROWS - 1 || column > COLUMNS - 1) {
        printf("Please enter row < %d and column < %d\n", ROWS, COLUMNS);
        fflush(stdout);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }


    // A two-dimensional cylindr of 12 processes in a 4x3 grid //
    dim[0] = COLUMNS;
    dim[1] = ROWS;
    period[0] = 0;
    period[1] = 0;
    reorder = 1;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, reorder, &comm);

    // Each process displays its rank and cartesian coordinates
    MPI_Cart_coords(comm, rank, 2, coord);
    printf("Rank %d coordinates are %d %d\n", rank, coord[0], coord[1]);
    fflush(stdout);

    if (rank == 0) {
        coord[0] = column;
        coord[1] = row;
        MPI_Cart_rank(comm, coord, &id);
        printf("The processor at position (%d, %d) has rank %d\n", coord[0], coord[1], id);
        fflush(stdout);
    }

    if (rank == 5) {
        MPI_Cart_shift(comm, 0, 1, &source, &dest);
        printf("Rank = %d Source = %d  Destination %d\n", rank, source, dest);
        fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}

