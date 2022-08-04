#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include "mpi.h"
#include "utils.h"

double matching(Picture *haystack, Object *needle, int start_row, int start_col, double expected_match_val) {
    double actual_match_val = 0;
#pragma omp parallel for collapse(2) reduction (+:actual_match_val) schedule(static) num_threads(8)
    for (int row = start_row; row < start_row + needle->size; row++) {
        for (int col = start_col; col < start_col + needle->size; col++) {
            if (actual_match_val < expected_match_val) {
                double p = (double) haystack->matrix[coord_to_index(row, col, haystack->size)];
                actual_match_val += fabs(p - needle->matrix[coord_to_index(row - start_row, col - start_col, needle->size)]) / p;
            }
        }
    }
    return actual_match_val;
}

void get_matches_for_picture(Picture *pic, Object *objects, int objs_size, double matching_val) {
    int diffs[objs_size];
    for (int i = 0; i < objs_size; i++) {
        diffs[i] = pic->size - objects[i].size + 1;
    }

    for (int obj_i = 0; obj_i < objs_size && pic->obj_id == -1; obj_i++) {
#pragma omp parallel for num_threads(diffs[obj_i])
        for (int row = 0; row < diffs[obj_i]; row++) {
#pragma omp parallel for num_threads(diffs[obj_i])
            for (int col = 0; col < diffs[obj_i]; col++) {
                if (pic->obj_id != -1) continue;
                if (matching(pic, objects + obj_i, row, col, matching_val) < matching_val) {
                    pic->match_row = row;
                    pic->match_col = col;
                    pic->obj_id = objects[obj_i].id;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int my_rank, num_of_processes;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_of_processes);

    int num_of_pics_per_process, num_of_remaining_pics = 0;
    double matching_val;
    int num_of_pics, num_of_objs;
    Picture *pic_arr;
    Object *obj_arr;
    double t1;

    if (my_rank == 0) { // master proc
        read_from_file(&matching_val, &num_of_pics, &num_of_objs, &pic_arr, &obj_arr);
        t1 = MPI_Wtime();

        // divide pictures between the num_of_processes and send all objects to all num_of_processes
        printf("num of total pics: %d\n", num_of_pics);
        printf("num of total processes: %d\n", num_of_processes);
        num_of_pics_per_process = num_of_pics / num_of_processes;
        num_of_remaining_pics = num_of_pics % num_of_processes;
        if (num_of_pics < num_of_processes) {
            printf("Start the program with number of processes >= number of pics");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        MPI_Bcast(&num_of_pics_per_process, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&num_of_processes, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&num_of_objs, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&matching_val, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        for (int slave = 1; slave < num_of_processes; slave++) {
            for (int pic_i = 0; pic_i < num_of_pics_per_process; ++pic_i) {
                int pic_size = pic_arr[slave * num_of_pics_per_process + pic_i].size;
                MPI_Send(&pic_arr[slave * num_of_pics_per_process + pic_i].id, 1, MPI_INT, slave, 0, MPI_COMM_WORLD);
                MPI_Send(&pic_size, 1, MPI_INT, slave, 0, MPI_COMM_WORLD);
                MPI_Send(pic_arr[slave * num_of_pics_per_process + pic_i].matrix, pic_size * pic_size, MPI_INT, slave,
                         0, MPI_COMM_WORLD);
            }
        }

        for (int obj_i = 0; obj_i < num_of_objs; obj_i++) {
            int obj_size = obj_arr[obj_i].size;
            MPI_Bcast(&obj_arr[obj_i].id, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Bcast(&obj_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Bcast(obj_arr[obj_i].matrix, obj_size * obj_size, MPI_INT, 0, MPI_COMM_WORLD);
        }

    } else {
        MPI_Bcast(&num_of_pics_per_process, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&num_of_processes, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&num_of_objs, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&matching_val, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        pic_arr = (Picture *) malloc(num_of_pics_per_process * sizeof(Picture));
        if (pic_arr == NULL) {
            printf("Error: malloc failed\n");
            exit(1);
        }

        for (int pic_i = 0; pic_i < num_of_pics_per_process; pic_i++) {
            MPI_Recv(&pic_arr[pic_i].id, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&pic_arr[pic_i].size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            pic_arr[pic_i].matrix = (int *) malloc(pic_arr[pic_i].size * pic_arr[pic_i].size * sizeof(int));

            if (pic_arr[pic_i].matrix == NULL) {
                printf("Error: malloc failed\n");
                exit(1);
            }

            MPI_Recv(pic_arr[pic_i].matrix, pic_arr[pic_i].size * pic_arr[pic_i].size, MPI_INT, 0, 0, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            pic_arr[pic_i].match_row = -1;
            pic_arr[pic_i].match_col = -1;
            pic_arr[pic_i].obj_id = -1;
        }

        obj_arr = (Object *) malloc(num_of_objs * sizeof(Object));
        if (obj_arr == NULL) {
            printf("Error: malloc failed\n");
            exit(1);
        }

        for (int obj_i = 0; obj_i < num_of_objs; obj_i++) {
            MPI_Bcast(&obj_arr[obj_i].id, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Bcast(&obj_arr[obj_i].size, 1, MPI_INT, 0, MPI_COMM_WORLD);
            int obj_size = obj_arr[obj_i].size;
            obj_arr[obj_i].matrix = (int *) malloc(obj_size * obj_size * sizeof(int));
            MPI_Bcast(obj_arr[obj_i].matrix, obj_size * obj_size, MPI_INT, 0, MPI_COMM_WORLD);
        }

    }

    // *********************** MATCHING ***************************

    for (int pic_index = 0; pic_index < num_of_pics_per_process; pic_index++) {
        printf("process #%d working on picture #%d\n", my_rank, pic_arr[pic_index].id);
        get_matches_for_picture(pic_arr + pic_index, obj_arr, num_of_objs, matching_val);
        printf("process #%d finished working on picture #%d\n", my_rank, pic_arr[pic_index].id);
    }

    int matches_info_for_all_pics[4 * num_of_pics];
    int matches_info_for_proc[4 * (num_of_pics_per_process + num_of_remaining_pics)];

    // master process deals with remaining pictures
    if (my_rank == 0) {
        for (int pic_i = num_of_processes * num_of_pics_per_process; pic_i < num_of_pics; pic_i++) {
            printf("process #%d working on picture #%d\n", my_rank, pic_arr[pic_i].id);
            get_matches_for_picture(pic_arr + pic_i, obj_arr, num_of_objs, matching_val);
            printf("process #%d finished working on picture #%d\n", my_rank, pic_arr[pic_i].id);
        }
    }

    // prepare matches details for sending back to master
    for (int pic_i = 0; pic_i < num_of_pics_per_process; pic_i++) {
        matches_info_for_proc[pic_i * 4] 	= pic_arr[pic_i].id;
        matches_info_for_proc[pic_i * 4 + 1] = pic_arr[pic_i].obj_id;
        matches_info_for_proc[pic_i * 4 + 2] = pic_arr[pic_i].match_row;
        matches_info_for_proc[pic_i * 4 + 3] = pic_arr[pic_i].match_col;
    }
    if (my_rank == 0) {
        for (int pic_i = num_of_processes * num_of_pics_per_process; pic_i < num_of_pics; pic_i++) {
            matches_info_for_all_pics[pic_i * 4] 	= pic_arr[pic_i].id;
            matches_info_for_all_pics[pic_i * 4 + 1] = pic_arr[pic_i].obj_id;
            matches_info_for_all_pics[pic_i * 4 + 2] = pic_arr[pic_i].match_row;
            matches_info_for_all_pics[pic_i * 4 + 3] = pic_arr[pic_i].match_col;
        }
    }

    if (my_rank != 0) { // slave proc
    	MPI_Gather(matches_info_for_proc, 4 * num_of_pics_per_process, MPI_INT, matches_info_for_all_pics, 4 * num_of_pics_per_process,
    	                   MPI_INT, 0, MPI_COMM_WORLD); // send matches details to master
    } else { // master proc
    	// receive match details from each process and updated the picture array according to the process rank
		MPI_Gather(matches_info_for_proc, 4 * num_of_pics_per_process, MPI_INT, matches_info_for_all_pics, 4 * num_of_pics_per_process,
				   MPI_INT, 0, MPI_COMM_WORLD);

		double t2 = MPI_Wtime();
		printf("\n~FINISHED | time elapsed = %1.9fs\n", t2 - t1);

		// write each final picture info to the output file
		for (int pic_i = 0; pic_i < num_of_pics; pic_i++) {
			write_to_file(
					matches_info_for_all_pics[pic_i * 4],		// pic id
					matches_info_for_all_pics[pic_i * 4 + 1],	// obj id	 (-1 if none)
					matches_info_for_all_pics[pic_i * 4 + 2],	// match row (-1 if none)
					matches_info_for_all_pics[pic_i * 4 + 3]	// match col (-1 if none)
			);
		}
    }

    if (my_rank == 0) puts("freeing...");

    for (int i = 0; i < (my_rank == 0 ? num_of_pics : num_of_pics_per_process); i++) {
        free(pic_arr[i].matrix);
    }
    for (int i = 0; i < num_of_objs; i++) {
        free(obj_arr[i].matrix);
    }
    free(pic_arr);
    free(obj_arr);

    MPI_Finalize();
    return 0;
}
