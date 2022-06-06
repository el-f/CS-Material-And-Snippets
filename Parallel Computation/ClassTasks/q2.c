#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROOT 2
#define K 3
void q1();
void q2();

int main(int argc, char *argv[]){
   
   MPI_Init(&argc, &argv);
  // q1(); 
   q2();
   MPI_Finalize();
   return 0;
}

void q1(){
	int rank, size, sum =0, totSum =0, temp = 0;
        int *numbers, nums[K];

        MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == ROOT){ 
	        numbers = (int*)malloc(sizeof(int) * size * K);
		for (int i = 0 ; i < size * K; i++) 
		        numbers[i] = i;
		nums[0] = numbers[6];
		nums[1] = numbers[7];
		nums[2] = numbers[8];
		for (int i = 0 ; i < size ; i++)
		    if (i != 2)
		       MPI_Send(&numbers[i * K], K , MPI_INT, i, 0, MPI_COMM_WORLD);
	}	
	else MPI_Recv(nums, K, MPI_INT, ROOT, 0, MPI_COMM_WORLD, &status);
	
	for (int i = 0 ; i < 3 ; i++)        
	       sum += nums[i];	
        printf("rank %d -- the sum %d\n",rank,sum);
        
        if (rank == ROOT) {
	        totSum = sum;
	        int temp;
                for ( int i = 0; i < size ; i++) {
                    if (i != 2) {
                        MPI_Recv(&temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
                        totSum += temp;
                    }
                }
                for ( int i = 0; i < size ; i++) {
                    if(i != 2)
                        MPI_Send(&totSum, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                }
        }
        else MPI_Send(&sum, 1, MPI_INT, ROOT, 0, MPI_COMM_WORLD);
        
        if(rank != 2)
            MPI_Recv(&totSum, 1, MPI_INT, ROOT, 0, MPI_COMM_WORLD, &status);
        printf("Rank %d -- The total sum %d\n", rank, totSum);          		
}



void q2() {
	MPI_Comm comm;
	int rank, size, sum = 0, totSum = 0;
        int *numbers, *sums, nums[K];

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

       int result[size];
       
	if (rank == 2){
	        numbers = (int*)malloc(sizeof(int) * size * K);
		for (int i = 0 ; i < size * K; i++) 
		        numbers[i] = i; 	
	}
	
	MPI_Scatter(numbers, K, MPI_INT, nums, K, MPI_INT, 2, MPI_COMM_WORLD);
	
	for( int i = 0 ; i < K ; i++ ) 
	   sum += nums[i];   

	MPI_Gather(&sum, 1, MPI_INT, result, 1, MPI_INT, 2, MPI_COMM_WORLD);

	if (rank == 2){
            for (int i = 0 ; i < size ; i++) 
                totSum += result[i];
	}
	
	MPI_Bcast(&totSum, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
        printf("rank %d -- total sum %d\n",rank,totSum);
}





