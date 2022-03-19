#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <mpi.h>

// authors: Elazar Fine, Maor Ofek

#define FILE_NAME "points.txt"
#define ANSWERS_TAG 1

// This function simulates heavy computations,
// its run time depends on x, y and param values
// DO NOT change this function!!
double heavy(double x, double y, int param) {
    double center[2] = {0.4, 0.2};
    int i, loop, size = 1, coeff = 10000;
    double sum = 0, dx, dy, radius = 0.2 * size;
    int longLoop = 1000, shortLoop = 1;
    double pi = 3.14;
    dx = (x - center[0]) * size;
    dy = (y - center[1]) * size;
    loop = (sqrt(dx * dx + dy * dy) < radius) ? longLoop : shortLoop;

    for (i = 1; i < loop * coeff; i++)
        sum += cos(2 * pi * dy * dx + 0.1) * sin(exp(10 * cos(pi * dx))) / i;

    return sum;
}

// Reads data from the file and allocates the array of points
// The first line contains a parameter
// The second line contains a number of points defined.
// Following lines contain two doubles each - point coordinates x, y
double *read_from_file(const char *fileName, int *numberOfPoints, int *param) {
    FILE *fp;
    double *points;

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
    points = (double *) malloc(2 * *numberOfPoints * sizeof(double));
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

double max_in_range(int start, int end, double *points, int param) {
    int i;
    double max = 0;
    for (i = start; i < end; i++) {
        max = fmax(max, heavy(points[2 * i], points[2 * i + 1], param));
    }
    return max;
}

int main(int argc, char *argv[]) {
    double answer = 0;
    int num_of_points = 10;
    double *points, x, y;
    int param;
    int numprocs, myid, tasks_per_proc, remainder;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    // Read points from the file
    points = read_from_file(FILE_NAME, &num_of_points, &param);
    tasks_per_proc = num_of_points / numprocs;
    remainder = num_of_points % numprocs;

    double t1 = MPI_Wtime();

    //Each process calculates his tasks - if more processes than tasks, each calculates one
    if (numprocs >= num_of_points) {
        if (myid <= num_of_points) {
            answer = fmax(answer, heavy(points[myid], points[myid + 1], param));
            remainder = 0;
        }
    } else {
        answer = max_in_range(myid * tasks_per_proc, myid * tasks_per_proc + tasks_per_proc, points, param);
    }

    if (myid == 0) { // master proc
        int i;
        double temp_ans;

        //calculate answers for all remaining tasks
        answer = fmax(answer, max_in_range(num_of_points - remainder, num_of_points, points, param));

        //get answers from slaves
        for (i = 1; i < numprocs; i++) {
            MPI_Recv(&temp_ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, ANSWERS_TAG, MPI_COMM_WORLD, &status);
            answer = fmax(answer, temp_ans);
        }

        double t2 = MPI_Wtime();
        printf("answer = %e\ntime = %1.9f\n", answer, t2 - t1);
    } else { // slave proc
        // send answer to master
        MPI_Send(&answer, 1, MPI_DOUBLE, 0, ANSWERS_TAG, MPI_COMM_WORLD);
    }

    free(points);
    MPI_Finalize();
    return 0;
}
