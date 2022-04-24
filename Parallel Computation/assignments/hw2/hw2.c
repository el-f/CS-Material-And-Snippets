#include "mpi.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "data.txt"
#define PACK_SIZE 255

char **read_file(const char *file, int *K, int *N, int *iter, char **sub_str) {
    FILE *fp;
    char **strings;

    if ((fp = fopen(file, "r")) == 0) {
        printf("Failed opening file [%s]\n", file);
        exit(1);
    }

    if ((fscanf(fp, "%d", K) & fscanf(fp, "%d", N) & fscanf(fp, "%d", iter))
        == 0) {
        printf("Failed reading file [%s]\n", file);
        exit(1);
    }

    char temp[(*N * 2) + 1];
    fscanf(fp, "%s", temp);

    *sub_str = strdup(temp);

    strings = (char **) malloc(*K * *K * sizeof(char *));
    if (strings == NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    for (int i = 0; i < *K * *K; i++) {
        strings[i] = (char *) malloc((1 + *N * 2) * sizeof(char));
        if (strings[i] == NULL) {
            printf("malloc failed\n");
            exit(1);
        }
        fscanf(fp, "%s", temp);
        strings[i] = strdup(temp);
    }

    fclose(fp);
    return strings;
}

// setup procedure for master process
void master_setup(int *K, int size, int pck_idx, int *N, int *iterations,
                  char **sub_str, char *pack, char **curr_str) {
    char **strings = read_file(FILE_NAME, K, N, iterations, sub_str); //read info from file
    if (*K * *K != size) {
        printf("Please Run With %d Processes\n", *K * *K);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    printf("Initialized K = %d, N = %d\n", *K, *N);
    printf("Searching for substring `%s`, in maximum %d iterations\n\n",
           *sub_str, *iterations);
    int ss_len = strlen(*sub_str) + 1; // +1 for null terminator
    // pack all data
    MPI_Pack(K, 1, MPI_INT, pack, PACK_SIZE, &pck_idx, MPI_COMM_WORLD);
    MPI_Pack(N, 1, MPI_INT, pack, PACK_SIZE, &pck_idx, MPI_COMM_WORLD);
    MPI_Pack(iterations, 1, MPI_INT, pack, PACK_SIZE, &pck_idx, MPI_COMM_WORLD);
    MPI_Pack(&ss_len, 1, MPI_INT, pack, PACK_SIZE, &pck_idx, MPI_COMM_WORLD);
    MPI_Pack(*sub_str, ss_len, MPI_CHAR, pack, PACK_SIZE, &pck_idx, MPI_COMM_WORLD);

    // broadcast pack to slaves
    MPI_Bcast(pack, PACK_SIZE, MPI_PACKED, 0, MPI_COMM_WORLD);
    *curr_str = (char *) malloc((*N * 2 + 1) * sizeof(char));
    if (*curr_str == NULL) {
        printf("malloc failed\n");
        exit(1);
    }
    *curr_str = strdup(strings[0]); // initial

    // send strings to all other procs (the slaves)
    for (int i = 1; i < *K * *K; i++) {
        MPI_Send(strings[i], 2 * *N, MPI_CHAR, i, 0, MPI_COMM_WORLD);
    }

    for (int i = 0; i < *K * *K; i++) {
        free(strings[i]);
    }
    free(strings);
}

// setup procedure for slave process
void slave_setup(int pck_idx, int *K, char *pack, int *N, int *iterations,
                 char **sub_str, char **curr_str, MPI_Status *status) {

    int ss_len;
    // get pack
    MPI_Bcast(pack, PACK_SIZE, MPI_PACKED, 0, MPI_COMM_WORLD);

    // unpack data received
    MPI_Unpack(pack, PACK_SIZE, &pck_idx, K, 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Unpack(pack, PACK_SIZE, &pck_idx, N, 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Unpack(pack, PACK_SIZE, &pck_idx, iterations, 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Unpack(pack, PACK_SIZE, &pck_idx, &ss_len, 1, MPI_INT, MPI_COMM_WORLD);

    *sub_str = (char *) malloc(ss_len * sizeof(char));
    if (*sub_str == NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    // get sub_str from master proc
    MPI_Unpack(pack, PACK_SIZE, &pck_idx, *sub_str, ss_len, MPI_CHAR, MPI_COMM_WORLD);

    *curr_str = (char *) malloc((2 * *N + 1) * sizeof(char));
    if (*curr_str == NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    // get initial string
    MPI_Recv(*curr_str, 2 * *N, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, status);
}

int do_iteration(int my_rank, int K, int N, char *curr_str, int up, int down,
                 int left, int right, char *sub_str, MPI_Comm comm, MPI_Status *status,
                 int *found_flags) {
    char from_right[N], from_down[N], to_left[N], to_up[N];
    strcpy(to_left, "");
    strcpy(to_up, "");
    int found_one = 0;

    //create new strings to send
    for (int i = 0; i < N * 2 + 2; i++) {
        if (i % 2 == 0) {
            to_up[i / 2] = curr_str[i];
        } else {
            to_left[i / 2] = curr_str[i];
        }
    }

    // exchange string parts with neighbors
    MPI_Send(to_up, N + 1, MPI_CHAR, up, 0, comm);                  // send to up
    MPI_Recv(from_down, N + 1, MPI_CHAR, down, 0, comm, status);    // receive from down
    MPI_Send(to_left, N + 1, MPI_CHAR, left, 0, comm);              // send left
    MPI_Recv(from_right, N + 1, MPI_CHAR, right, 0, comm, status);  // receive from right

    // update current string to concatenated received parts
    strcat(from_right, from_down);
    strcpy(curr_str, from_right);

    // check if current string contains the required sub string.
    int found = strstr(curr_str, sub_str) != NULL;

    // synchronize found_flags
    MPI_Allgather(&found, 1, MPI_INT, found_flags, 1, MPI_INT, comm);

    // check if found at least once
    for (int i = 0; i < K * K; i++) {
        found_one |= found_flags[i];
    }

    if (found_one) {
        if (my_rank == 0) {
            puts("\n Substring found!\n");
            printf("Rank %-2d | String %s\n", my_rank, curr_str);
            for (int i = 1; i < K * K; i++) {
                MPI_Recv(curr_str, 2 * N, MPI_CHAR, i, 0, comm, status);
                printf("Rank %-2d | String %s\n", i, curr_str);
            }
        } else { //if process is slave sent his current string
            MPI_Send(curr_str, 2 * N, MPI_CHAR, 0, 0, comm);
        }
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int K, N, iterations, my_rank, size;
    char *sub_str, *curr_str;
    int pck_idx = 0, found_one = 0;
    int *found_flags;

    MPI_Status status;
    MPI_Comm comm;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    found_flags = (int *) malloc(size * sizeof(int));
    if (found_flags == NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    char *pack = (char *) malloc(PACK_SIZE * sizeof(char));
    if (pack == NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    if (my_rank == 0) { // master proc
        master_setup(&K, size, pck_idx, &N, &iterations, &sub_str, pack, &curr_str);
    } else { // slave proc
        slave_setup(pck_idx, &K, pack, &N, &iterations, &sub_str, &curr_str, &status);
    }

    int dim[2], period[2];
    dim[0] = K;     // size of matrix
    dim[1] = K;     // size of matrix
    period[0] = 1;  // enable circular matrix
    period[1] = 1;  // enable circular matrix

    MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, 1, &comm); // create K * K matrix of procs

    int left, right, up, down;
    // get neighbors ids
    MPI_Cart_shift(comm, 0, 1, &up, &down);
    MPI_Cart_shift(comm, 1, 1, &left, &right);

    for (int it = 0; it < iterations; it++) {
        if (my_rank == 0)
            printf("performing iteration #%d\n", it + 1);
        if (do_iteration(my_rank, K, N, curr_str, up, down, left, right, sub_str, comm, &status, found_flags)) {
            found_one = 1;
            break;
        }
    }

    if (my_rank == 0 && !found_one) {
        printf("The substring was not found!\n");
    }

    free(pack);
    free(sub_str);
    free(curr_str);
    free(found_flags);

    MPI_Finalize();
    return 0;
}
