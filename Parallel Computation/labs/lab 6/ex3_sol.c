#include<mpi.h>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Define parameters from the arguments passed to the main
void defineParameters(int argc, char *argv[], int *K, int *N, int *r) {
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (argc != 4) {
        printf("Please run three parametrs  K, N, r \n");
        fflush(stdout);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    *K = atoi(argv[1]);
    *N = atoi(argv[2]);
    *r = atoi(argv[3]);
    if (size != (*K) * (*N)) {
        printf("Please run with %d processes.\n", size);
        fflush(stdout);
        MPI_Abort(MPI_COMM_WORLD, 2);
    }
}

// Process 0 collects all values and finds the rank with maximum value
// It is known for rank 0 only
int rankWithMaxValue(int value) {
    int *array = NULL;
    int rank, size, i;
    int rankMax;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        array = (int *) malloc(size * sizeof(int));
        if (array == NULL) {
            printf("Cannnot allocate the memorry\n");
            fflush(stdout);
            MPI_Abort(MPI_COMM_WORLD, 3);
        }
    }

    MPI_Gather(&value, 1, MPI_INT, array, 1, MPI_INT, 0, MPI_COMM_WORLD);


    if (rank == 0) {
        rankMax = 0;
        for (i = 1; i < size; i++)
            if (array[i] > array[rankMax])
                rankMax = i;
    }

    free(array);

    return rankMax;
}

// Create K*N Grid
MPI_Comm createGrid(int K, int N) {
    MPI_Comm comm;
    int dim[2], period[2], reorder;
    dim[0] = K;
    dim[1] = N;
    period[0] = 0;
    period[1] = 0;
    reorder = 1;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, reorder, &comm);
    return comm;
}

// Find the distance between ranks r and rankMax
void findDistance(int r, int rankMax, MPI_Comm comm) {
    int coordR[2], coordMax[2], distance;

    MPI_Cart_coords(comm, r, 2, coordR);
    MPI_Cart_coords(comm, rankMax, 2, coordMax);
    distance = abs(coordR[0] - coordMax[0]) + abs(coordR[1] - coordMax[1]);
    printf("The distance between ranks %d and %d is equal %d\n", r, rankMax, distance);
}

int main(int argc, char *argv[]) {
    MPI_Comm comm;
    int K, N, r;
    int value;
    int rank, rankMax;
    int coordR[2];

    MPI_Init(&argc, &argv);

    // Parameters from command line
    defineParameters(argc, argv, &K, &N, &r);

    // Define a random value
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srand(time(NULL) + rank);
    value = rand() % 1000;

    // Find a rank with maximum value
    rankMax = rankWithMaxValue(value);

    // Create KxN grid
    comm = createGrid(K, N);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Cart_coords(comm, rank, 2, coordR);
    printf("rank = %d   (%d, %d) value = %d\n", rank, coordR[0], coordR[1], value);

    // Find the Distance
    if (rank == 0)
        findDistance(r, rankMax, comm);

    MPI_Finalize();
    return 0;
}
