#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROOT 2
#define N 8

void c();
void d();

int main(int argc, char *argv[]) {

	MPI_Init(&argc, &argv);
	//c();
	d();
	MPI_Finalize();
       return 0;
}

void c() {
   int rank, size, x, y;
   double t1, t2;
        
   MPI_Status status;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   t1  = MPI_Wtime();

   if (rank == 0) {
      x = rand() % 10;
      MPI_Send(&x, 1, MPI_INT, 1, 0,MPI_COMM_WORLD);
   }
   else {
      MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      y = x * 10;
      MPI_Send(&y, 1, MPI_INT, 0, 0,MPI_COMM_WORLD);
   }
        
   if (rank == 0)
      MPI_Recv(&y, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
   printf("rank = %d -- x = %d  y = %d\n",rank,x,y);
   t2 = MPI_Wtime();
   printf("MPI_Wtime measured a 1 second sleep to be: %1.2f\n",t2-t1); fflush(stdout);
}

void d() {
   int rank, size, pos = 0, neg = 0, num, result;
   int* A = (int*)malloc(sizeof(int) * N);
   int B[N];
   double t1, t2;
        
   MPI_Status status;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   t1  = MPI_Wtime();

   if (rank == 0) { //MASTER
      int temp[N] = { 2, -1, 9, 0, -7, -2, -4, 9};
      for (int i = 0 ; i < N ; i++)  {   
          A[i] = temp[i];
          MPI_Send(&A[i], 1, MPI_INT, i+1, 0,MPI_COMM_WORLD);
      }
   } 
   else { //sleve
         MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
         result = (num < 0)? 0:1;
         MPI_Send(&result, 1, MPI_INT, 0, 0,MPI_COMM_WORLD);        
   }
       
   if (rank == 0) {
      for (int i = 0 ; i < N ; i++)  {   
          MPI_Recv(&result, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD, &status);
          (result == 1)? pos++:neg++;
      }
      printf("pos = %d -- neg = %d \n",pos,neg);
      t2 = MPI_Wtime();
      printf("MPI_Wtime measured a 1 second sleep to be: %1.2f\n",t2-t1); fflush(stdout);
   }
}




