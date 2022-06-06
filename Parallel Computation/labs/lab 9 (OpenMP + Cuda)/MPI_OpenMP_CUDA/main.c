#include <mpi.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include "myProto.h"

/*
Simple MPI+OpenMP+CUDA Integration example
Initially the array of size 4*PART is known for the process 0.
It sends the half of the array to the process 1.
Both processes start to increment members of thier members by 1 - partially with OpenMP, partially with CUDA
The results is send from the process 1 to the process 0, which perform the test to verify that the integration worked properly
*/
 

int main(int argc, char *argv[]) {
    int size, rank, i;
    int *data;
    MPI_Status  status;

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
       for (i = 0;  i < 4*PART;  i++)
          data[i] = i;
       MPI_Send(data + 2*PART, 2*PART, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else {
       // Allocate memory and reieve a half of array from other process
       if ((data = (int *) malloc(2*PART*sizeof(int))) == NULL)
          MPI_Abort(MPI_COMM_WORLD, __LINE__);
       MPI_Recv(data, 2*PART, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }
  
    // On each process - perform a first half of its task with OpenMP     
#pragma omp parallel for
    for (i = 0;   i < PART;   i++)       
        data[i]++;       
		
    // On each process - perform a second half of its task with CUDA
    if (computeOnGPU(data + PART, PART) != 0)
       MPI_Abort(MPI_COMM_WORLD, __LINE__);

    // Collect the result on one of processes
    if (rank == 0) 
       MPI_Recv(data + 2*PART, 2*PART, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
    else 
       MPI_Send(data, 2*PART, MPI_INT, 0, 0, MPI_COMM_WORLD);

    // Perform a test just to verify that integration MPI + OpenMP + CUDA worked as expected
    if (rank == 0)
       test(data, 4*PART);

    MPI_Finalize();

    return 0;
}


