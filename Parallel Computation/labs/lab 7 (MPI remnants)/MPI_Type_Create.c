#include "mpi.h"
#include <stdio.h>

struct Particle {
    float x;
    float y;
    int color;
};

int main(int argc, char *argv[]) {
    struct Particle particle;
    int myrank, size;
    MPI_Status status;
    MPI_Datatype ParticleMPIType;
    MPI_Datatype type[3] = {MPI_FLOAT, MPI_FLOAT, MPI_INT};
    int blocklen[3] = {1, 1, 1};
    MPI_Aint disp[3];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 2) {
        printf("Please run with 2 processes.\n");
        fflush(stdout);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }


    // Create MPI user data type for partical
    disp[0] = (char *) &particle.x - (char *) &particle;
    disp[1] = (char *) &particle.y - (char *) &particle;
    disp[2] = (char *) &particle.color - (char *) &particle;
    MPI_Type_create_struct(3, blocklen, disp, type, &ParticleMPIType);
    MPI_Type_commit(&ParticleMPIType);


    // Send and recieve one struct of the ParticleMPIType type
    if (myrank == 0) {
        particle.x = 1.1;
        particle.y = 2.2;
        particle.color = 3;
        printf("myrank = %d x = %e  y = %e  color = %d\n", myrank, particle.x, particle.y, particle.color);
        MPI_Send(&particle, 1, ParticleMPIType, 1, 0, MPI_COMM_WORLD);
    } else if (myrank == 1) {
        struct Particle part;
        MPI_Recv(&part, 1, ParticleMPIType, 0, 0, MPI_COMM_WORLD, &status);
        printf("myrank = %d x = %e  y = %e  color = %d\n", myrank, part.x, part.y, part.color);
    }
    MPI_Finalize();
    return 0;
}


