#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <mpi.h>

// authors: Elazar Fine, Maor Ofek

#define FILE_NAME "points.txt"
#define START_JOB_TAG 0
#define FINISH_JOB_TAG 1
#define TERMINATE_PROCESS_TAG 2

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

// get next point to calculate from the array
void get_next_job(double *x, double *y, const double *points, int *curr_point) {
    *x = points[2 * *curr_point];
    *y = points[2 * *curr_point + 1];
    *curr_point += 1;
}

// master routine - task allocation management, then returning final answer
double manage_tasks_and_get_ans(int numprocs, int num_of_points, double *points) {
    MPI_Status status;
    double point[2];
    double max = 0, temp_ans;
    int i, num_assign, working_processes_count = 0;
    int curr_point = 0;
    // assign tasks to all processes
    for (i = 1; i < numprocs && curr_point < num_of_points; i++) {
        get_next_job(&point[0], &point[1], points, &curr_point);
        MPI_Send(point, 2, MPI_DOUBLE, i, START_JOB_TAG, MPI_COMM_WORLD);
        working_processes_count++;
    }

    while (curr_point < num_of_points || working_processes_count > 0) {
        // waits for one of the processes to return with an answer, and assigns it a new point to process
        MPI_Recv(&temp_ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, FINISH_JOB_TAG, MPI_COMM_WORLD, &status);
        max = fmax(max, temp_ans);
        if (curr_point < num_of_points) {
            // process returned and there are more tasks left - assign new task
            int process_id = status.MPI_SOURCE;
            get_next_job(&point[0], &point[1], points, &curr_point);
            MPI_Send(point, 2, MPI_DOUBLE, process_id, START_JOB_TAG, MPI_COMM_WORLD);
        } else {
            // process returned and no more tasks left - continue
            working_processes_count--;
        }
    }

    return max;
}

// slave routine - listen for tasks and execute
void listen_and_exec(int param) {
    MPI_Status status;
    int tag;
    double xy[2];
    double answer;
    do {
        MPI_Recv(xy, 2, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if ((tag = status.MPI_TAG) == START_JOB_TAG) {
            answer = heavy(xy[0], xy[1], param);
            MPI_Send(&answer, 1, MPI_DOUBLE, 0, FINISH_JOB_TAG, MPI_COMM_WORLD);
        }
    } while (tag != TERMINATE_PROCESS_TAG);
}

// send termination tags to all processes after finishing calculation
void terminate_processes(int numprocs) {
    for (int i = 1; i < numprocs; i++) {
        MPI_Send(&i, 1, MPI_INT, i, TERMINATE_PROCESS_TAG, MPI_COMM_WORLD);
    }
}

int main(int argc, char *argv[]) {
    double answer = 0;
    int num_of_points = 10;
    double *points;
    int param;
    int numprocs, myid;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    // read points from the file
    points = read_from_file(FILE_NAME, &num_of_points, &param);

    double t1 = MPI_Wtime();

    // if there is only one process then there are no slaves to allocate tasks to.
    // if there are only two processes then there is only one slave to allocate to.
    // in both cases only one process will do all the work:
    // in case of 1 process - the master, in case of 2 processes - the slave.
    // in the second case (2 processes) we still prefer to do the work in the master process in order to avoid
    // wasting precious time and resources on the communication/messages between the two processes.
    if (numprocs == 1 || numprocs == 2) {
        if (myid == 0) {
            for (int i = 0; i < num_of_points; i++) {
                answer = fmax(answer, heavy(points[2 * i], points[2 * i + 1], param));
            }
            double t2 = MPI_Wtime();
            printf("answer = %e\ntime = %1.9f\n", answer, t2 - t1);
        }
    } else {
        if (myid == 0) {
            t1 = MPI_Wtime();
            answer = manage_tasks_and_get_ans(numprocs, num_of_points, points);
            terminate_processes(numprocs);
            double t2 = MPI_Wtime();
            printf("answer = %e\ntime = %1.9f\n", answer, t2 - t1);
        } else {
            listen_and_exec(param);
        }
    }

    free(points);
    MPI_Finalize();
    return 0;
}
