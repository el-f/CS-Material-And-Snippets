#include <mpi.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include "myProto.h"

// This function is a special - runs on Host and Device
double f(int index);

int main(int argc, char *argv[]) {
    int size, rank, i;
    int *data;
    MPI_Status  status;
    int resultOMP = 0, resultCUDA = 0, resultTotal = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 2) {
       printf("Run the example with two processes only\n");
       MPI_Abort(MPI_COMM_WORLD, __LINE__);
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Divide the tasks between both processes
    if (rank == 0) {
       // Allocate memory for the whole array and send a half of the array to other process
       if ((data = (int *) malloc(4*PART*sizeof(int))) == NULL)
          MPI_Abort(MPI_COMM_WORLD, __LINE__);
       
       srand(time(NULL));
       for (i = 0;  i < 4*PART;  i++)
          data[i] = rand()%1000;
       MPI_Send(data + 2*PART, 2*PART, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else {
       // Allocate memory and reieve a half of array from other process
       if ((data = (int *) malloc(2*PART*sizeof(int))) == NULL)
          MPI_Abort(MPI_COMM_WORLD, __LINE__);
       MPI_Recv(data, 2*PART, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }
  
    // On each process - perform a first half of its task with OpenMP    
#pragma omp parallel for reduction(+: resultOMP)
    for (i = 0;   i < PART;   i++)       
        if (f(data[i]) > 0)
        	resultOMP++;       
	
    // On each process - perform a second half of its task with CUDA
    if (computeOnGPU(data + PART, PART, &resultCUDA) != 0)
  	MPI_Abort(MPI_COMM_WORLD, __LINE__);

    // Collect the result on one of processes
    if (rank == 0) {
       MPI_Recv(&resultTotal, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
       resultTotal += resultOMP + resultCUDA;
    }
    else {
       resultTotal += resultOMP + resultCUDA;
       MPI_Send(&resultTotal, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Perform a test just to verify that integration MPI + OpenMP + CUDA worked as expected
    // Comment out the test to eliminate the sequencional computations - just to see how long it is
    if (rank == 0)
       test(data, 4*PART, resultTotal);

    MPI_Finalize();

    return 0;
}


