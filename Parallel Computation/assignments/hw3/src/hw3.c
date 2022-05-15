#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include "mpi.h"

#define FILENAME "input.dat"

double *read_input_data(int *size) {
    FILE *file;
    double *array;

    if ((file = fopen(FILENAME, "r")) == 0) {
        exit(0);
    }

    // Read array size from file
    fscanf(file, "%d", size);

    // Allocate mem for array
    array = (double *) malloc(*size * sizeof(double));
    if (array == NULL) {
        exit(0);
    }

    // Read values from file into array
    for (int i = 0; i < *size; i++) {
        fscanf(file, "%lf", &array[i]);
    }

    fclose(file);

    return array;
}

void calculate_half(const double *input_half, double *output_half, int array_len, int max) {
    double first_term = 0.54030230587; // cos(exp(sin(0)))

#pragma omp parallel for
    for (int i = 0; i < array_len; i++) {
        double temp, max_for_i = first_term;

        for (int j = 1; j <= max; j++) { // get max
            temp = cos(exp(sin(input_half[i] * j)));
            if (temp > max_for_i) max_for_i = temp;
        }
        output_half[i] = max_for_i;
    }
}

double sum_output_half(const double *output_half, int array_len) {
    double sum = 0;

#pragma omp parallel for reduction (+:sum) // parallel summation
    for (int i = 0; i < array_len; i++)
        sum += output_half[i];

    return sum;
}

int main(int argc, char *argv[]) {
    int my_rank, processes;
    int array_len, max, threads;
    double my_sum = 0;
    double *array, *input_half, *output_half;
    double start_time;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);

    if (my_rank == 0) {
        if (processes != 2) {
            puts("Error: This program requires exactly 2 processes");
            MPI_Abort(MPI_COMM_WORLD, 1);
            exit(0);
        }
        if (argc != 3) {
            puts("Usage: mpiexec -np 2 ./hw3 <max> <threads>");
            MPI_Abort(MPI_COMM_WORLD, 1);
            exit(0);
        }
        if ((max = atoi(argv[1])) < 0) {
            puts("Error: max must be a positive integer");
            MPI_Abort(MPI_COMM_WORLD, 1);
            exit(0);
        }
        if ((threads = atoi(argv[2])) < 0) {
            puts("Error: threads must be a positive integer");
            MPI_Abort(MPI_COMM_WORLD, 1);
            exit(0);
        }

        array = read_input_data(&array_len);

        MPI_Send(&array_len, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&max, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&threads, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&array_len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&max, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&threads, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }

    input_half = (double *) malloc((array_len / 2) * sizeof(double));
    if (input_half == NULL) {
        MPI_Abort(MPI_COMM_WORLD, 1);
        exit(0);
    }

    output_half = (double *) malloc((array_len / 2) * sizeof(double));
    if (output_half == NULL) {
        MPI_Abort(MPI_COMM_WORLD, 1);
        exit(0);
    }

    if (my_rank == 0) {
        MPI_Scatter(array, array_len / 2, MPI_DOUBLE, input_half, array_len / 2, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    } else {
        MPI_Scatter(NULL, 0, MPI_DOUBLE, input_half, array_len / 2, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    if (my_rank == 0) start_time = MPI_Wtime();

    omp_set_dynamic(0);
    omp_set_num_threads(threads);

    calculate_half(input_half, output_half, array_len / 2, max);
    my_sum = sum_output_half(output_half, array_len / 2);

    if (my_rank == 0) { // proc 0
        double sum_from_proc1;
        MPI_Recv(&sum_from_proc1, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status); // receive sum from proc 1
        my_sum += sum_from_proc1;
        printf("Result: %lf Time: %lf\n", my_sum,  MPI_Wtime() - start_time);
    } else {
        MPI_Send(&my_sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); // send sum to proc 0
    }

    MPI_Finalize();
    free(input_half);
    free(output_half);
    free(array);
    return 0;
}
