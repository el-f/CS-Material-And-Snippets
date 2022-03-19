#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <mpi.h>
#define FILE_NAME "points.txt"

// This function simulates heavy computations,
// its run time depends on x, y and param values
// DO NOT change this function!!
double heavy(double x, double y, int param) {
	double center[2] = { 0.4, 0.2 };
	int i, loop, size = 1, coeff = 10000;
	double sum = 0, dx, dy, radius = 0.2*size;
	int longLoop = 1000, shortLoop = 1;
	double pi = 3.14;
	dx = (x - center[0]) * size;
	dy = (y - center[1]) * size;
	loop = (sqrt(dx * dx + dy * dy) < radius) ? longLoop : shortLoop;

	for (i = 1; i < loop * coeff; i++)
		sum += cos(2*pi * dy * dx + 0.1) * sin(exp(10*cos(pi* dx))) / i;

	return  sum;
}

// Reads data from from the file and allocates the array of points
// The first line contains a parameter
// The second line contains a number of points defined.
// Following lines contain two doubles each - point coordinates x, y
double* readFromFile(const char* fileName, int* numberOfPoints, int *param) {
	FILE* fp;
	double* points;

	// Open file for reading points
	if ((fp = fopen(fileName, "r")) == 0) {
		printf("cannot open file %s for reading\n", fileName);
		exit(0);
	}

	// Param
	fscanf(fp, "%d", param);

	// Number of points
	fscanf(fp, "%d", numberOfPoints);

	// Allocate array of points end Read data from the file
	points = (double*)malloc(2 * *numberOfPoints * sizeof(double));
	if (points == NULL) {
		printf("Problem to allocate memory\n");
		exit(0);
	}
	for (int i = 0; i < *numberOfPoints; i++) {
		fscanf(fp, "%le %le", &points[2 * i], &points[2 * i + 1]);
	}

	fclose(fp);

	return points;
}

int main(int argc, char* argv[]) {
	double answer = 0;
	int numberOfPoints = 10;
	double *points, x, y;
	int param;
	int numprocs, myid;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
		
	// Read points from the file
	points = readFromFile(FILE_NAME, &numberOfPoints, &param);
	
	double t1 = MPI_Wtime();
	// Find maximum value of heavy calculated for each point
	x = points[0];
	y = points[1];
	answer = heavy(x, y, param);

	// Perform heavy sequential computation
	for (int i = 1; i < numberOfPoints; i++) {
		x = points[2 * i];
		y = points[2 * i + 1];
		answer = fmax(answer, heavy(x, y, param));
	}
	double t2 = MPI_Wtime();
	printf("answer = %e\ntime = %1.9f\n", answer, t2 - t1);


	return 1;
}
