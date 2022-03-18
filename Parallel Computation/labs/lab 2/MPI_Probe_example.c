#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char **argv) {
    int myid, numprocs;
    MPI_Status status;
    int count;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);


    if (myid == 0) {
        int data[3] = {200, 300, 400};
        MPI_Send(data, 3, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else {
        int *msg, j;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

        MPI_Get_count(&status, MPI_INT, &count);
        printf("getting count = %d\n", count);

        msg = (int *) malloc(count * sizeof(int));

        MPI_Recv(msg, count, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        for (j = 0; j < count; j++) {
            printf("%d ", msg[j]);
        }
        printf("\n");

    }
    MPI_Finalize();
}
