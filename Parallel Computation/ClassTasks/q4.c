#include "mpi.h"
#include <stdio.h>

struct Data {
   float a[3];
   int b;
   double c;
}; 


int main(int argc, char *argv[]) {
     struct Data data;
     int rank, size;
     
     MPI_Status status;
     
     MPI_Datatype DataMPIType;
     MPI_Datatype type[3] = {MPI_FLOAT,MPI_INT,MPI_DOUBLE};
     int blocklen[3] = { 1, 1 ,1 };
     MPI_Aint disp[3];
     
     MPI_Init(&argc, &argv);
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     MPI_Comm_size(MPI_COMM_WORLD, &size);
     
     if (size != 2) {
          printf("Please run with 2  proces\n");fflush(stdout);
          MPI_Abort(MPI_COMM_WORLD, 1);
     }
     
     //Create MPI user data type for "data"
     disp[0] = (char*) &data.a - (char*)&data;
     disp[1] = (char*) &data.b - (char*)&data;
     disp[2] = (char*) &data.c - (char*)&data;
     MPI_Type_create_struct(3, blocklen, disp, type, &DataMPIType);
     MPI_Type_commit(&DataMPIType);
     
     
     if (rank != 0) {
         data.a[0] = 10;
         data.a[1] = 20;
         data.a[2] = 30;
         data.b = 40;
         data.c = 50.0;
         MPI_Send(&data, 1, DataMPIType, 0, 0, MPI_COMM_WORLD);
     }
     else {
         data.a[0] = 1;
         data.a[1] = 2;
         data.a[2] = 3;
         data.b = 4;
         data.c = 5.6;
         struct Data data2;
         MPI_Recv(&data2, 1, DataMPIType, 1, 0, MPI_COMM_WORLD, &status);
         
         struct Data totData;
         totData.a[0] = data.a[0] + data2.a[0];
         totData.a[1] = data.a[1] + data2.a[1];
         totData.a[2] = data.a[2] + data2.a[2];
         totData.b = data.b + data2.b;
         totData.c = data.c + data2.c;
         
         printf("a = {%.1f,%.1f,%.1f} -- b = %d -- c = %.1f\n",totData.a[0], totData.a[1], totData.a[2], totData.b, totData.c);
     }
     
     

}
