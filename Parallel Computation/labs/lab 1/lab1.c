#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
	int  my_rank; /* rank of process */
	int  p;       /* number of processes */
	int source;   /* rank of sender */
	int dest;     /* rank of receiver */
	int tag=0;    /* tag for messages */
	char message[100];        /* storage for message */
	MPI_Status status ;   /* return status for receive */
	
	/* start up MPI */
	
	MPI_Init(&argc, &argv);
	
	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
	
	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &p); 
	int s, r;

	if (my_rank !=0) {
		/* create message */
		sprintf(message, "Hello MPI World from process %d!", my_rank);
		
		MPI_Recv(&r, 4, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		s = 2 * r;
		printf("<process 1> sending:%d\n", s);
		MPI_Send(&s, 4, MPI_INT, 0, 2, MPI_COMM_WORLD);
	} else {
		srand(time(NULL));   	  
		s = rand() % 10 + 1; 
		printf("<process 0> sending:%d\n", s);
		MPI_Send(&s, 4, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Recv(&r, 4, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
		printf("<process 0> sent: %d, recieved: %d\n", s, r);
	}
	/* shut down MPI */
	MPI_Finalize(); 
	
	
	return 0;
}