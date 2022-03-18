#include "mpi.h"
#include <stdio.h>


#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {
    int rank, numprocs;
    int i;
    float f[3];
    char c;
    char buffer[BUFFER_SIZE];
    int position;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    // Check that there is exactly two proceeses
    if (numprocs != 2)
        MPI_Abort(MPI_COMM_WORLD, 0);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // Define the data
        i = 123;
        f[0] = 200.2f;
        f[1] = 201.3f;
        f[2] = 202.4f;
        c = '#';

        // Start packing from the very beginning of the buffer
        position = 0;
        MPI_Pack(&i, 1, MPI_INT, buffer, BUFFER_SIZE, &position, MPI_COMM_WORLD);
        MPI_Pack(f, 3, MPI_FLOAT, buffer, BUFFER_SIZE, &position, MPI_COMM_WORLD);
        MPI_Pack(&c, 1, MPI_CHAR, buffer, BUFFER_SIZE, &position, MPI_COMM_WORLD);

        // Send the packed message
        MPI_Send(buffer, position, MPI_PACKED, 1, 0, MPI_COMM_WORLD);
        printf("rank %d sends %d %5.1f %5.1f %5.1f %c\n", rank, i, f[0], f[1], f[2], c);
    }

    if (rank == 1) {

        // Recieve the packed message
        MPI_Recv(buffer, BUFFER_SIZE, MPI_PACKED, 0, 0, MPI_COMM_WORLD, &status);

        // Start unpacking to the very beginning of the buffer
        position = 0;
        MPI_Unpack(buffer, BUFFER_SIZE, &position, &i, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, BUFFER_SIZE, &position, f, 3, MPI_FLOAT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, BUFFER_SIZE, &position, &c, 1, MPI_CHAR, MPI_COMM_WORLD);
        printf("rank %d recieved %d %5.1f %5.1f %5.1f %c\n", rank, i, f[0], f[1], f[2], c);
    }

    MPI_Finalize();
    return 0;
}

