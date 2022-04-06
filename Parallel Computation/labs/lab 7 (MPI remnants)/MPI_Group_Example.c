#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MESSAGE_SIZE 6

int main(int argc, char *argv[]) {
    MPI_Group newGroup, worldGroup;
    int ranks[16] = {2, 4, 7}, size, newSize, newRank, rank;
    char msg[MESSAGE_SIZE] = {'\0'};
    MPI_Comm newComm;
    MPI_Status status;

    MPI_Init(0, 0);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 8) {
        printf("Test requires more than 8 processors\n");
        MPI_Abort(MPI_COMM_WORLD, __LINE__);
    }

    // get the World group
    MPI_Comm_group(MPI_COMM_WORLD, &worldGroup);

    // Create a new group into the World Group
    MPI_Group_incl(worldGroup, 3, ranks, &newGroup);

    // Check the size and ranks in the resulting group
    MPI_Group_size(newGroup, &newSize);
    MPI_Group_rank(newGroup, &newRank);

    printf("rank %d has newRank %d in newGroup, newSize is %d \n", rank, newRank, newSize);

    // Get communicator of the new group
    MPI_Comm_create(MPI_COMM_WORLD, newGroup, &newComm);

    // Broadcast in for new group only
    if (newRank == 0)
        strcpy(msg, "Hello");

    if (rank == ranks[0] || rank == ranks[1] || rank == ranks[2])
        MPI_Bcast(msg, 6, MPI_CHAR, 0, newComm);

    printf("rank = %d   after broadcast: msg = %s\n", rank, msg);

    if (newRank == 1) {
        int value = 123;
        MPI_Send(&value, 1, MPI_INT, 0, 0, newComm);
    } else if (newRank == 0) {
        int data;
        MPI_Recv(&data, 1, MPI_INT, 1, 0, newComm, &status);
        printf("newRank 1 received %d from newRank 0\n", data);
    }

    MPI_Group_free(&newGroup);

    MPI_Finalize();

    return 0;
}

