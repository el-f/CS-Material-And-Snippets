#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

void write_to_file(int picture_id, int object_id, int row, int col) {
    FILE *file;
    if ((file = fopen(OUTPUT_FILE, "a")) == 0) {
        printf("Failed opening file [%s]\n", OUTPUT_FILE);
        exit(1);
    }
    if (object_id != -1) {
        fprintf(file, "Picture %d: found Object %d in Position(%d,%d)\n",
                picture_id, object_id, row, col);
    } else {
        fprintf(file, "Picture %d: No Objects were found\n", picture_id);
    }

	if (object_id != -1) {
		printf("Picture %d: found Object %d in Position(%d,%d)\n",
			   picture_id, object_id, row, col);
	} else {
		printf("Picture %d: No Objects were found\n", picture_id);
	}

    fclose(file);
}

Picture *read_pictures(FILE *file_ptr, int num_of_mats) {
    Picture *pic_arr = (Picture *) malloc(num_of_mats * sizeof(Picture));
    if (!pic_arr) {
        printf("pic_arr malloc error!");
        return NULL;
    }

    for (int i = 0; i < num_of_mats; i++) {
        fscanf(file_ptr, "%d", &pic_arr[i].id);
        fscanf(file_ptr, "%d", &pic_arr[i].size);

        pic_arr[i].matrix = (int *) malloc(sizeof(int) * pic_arr[i].size * pic_arr[i].size);
        if (pic_arr[i].matrix == NULL) {
            printf("malloc error at pic_arr[%d]->matrix\n", i);
            return NULL;
        }
        for (int k = 0; k < pic_arr[i].size * pic_arr[i].size; k++) {
            fscanf(file_ptr, "%d", &pic_arr[i].matrix[k]);
        }
        pic_arr[i].match_row = -1;
        pic_arr[i].match_col = -1;
        pic_arr[i].obj_id = -1;
    }
    return pic_arr;
}

Object *read_objects(FILE *file_ptr, int num_of_mats) {
    Object *obj_arr = (Object *) malloc(num_of_mats * sizeof(Object));
    if (!obj_arr) {
        printf("obj_arr malloc error!");
        return NULL;
    }

    for (int i = 0; i < num_of_mats; i++) {
        fscanf(file_ptr, "%d", &obj_arr[i].id);
        fscanf(file_ptr, "%d", &obj_arr[i].size);

        obj_arr[i].matrix = (int *) malloc(sizeof(int) * obj_arr[i].size * obj_arr[i].size);
        if (obj_arr[i].matrix == NULL) {
            printf("malloc error at obj_arr[%d]->matrix\n", i);
            return NULL;
        }
        for (int k = 0; k < obj_arr[i].size * obj_arr[i].size; k++) {
            fscanf(file_ptr, "%d", &obj_arr[i].matrix[k]);
        }
    }
    return obj_arr;
}

// Read the file
void read_from_file(double *matching_val, int *num_of_pics, int *num_of_objs,
                    Picture **pic_arr, Object **obj_arr) {
    FILE *file_ptr;

    if ((file_ptr = fopen(INPUT_FILE, "r")) == 0) {
        printf("Cannot open file %s\n", INPUT_FILE);
        exit(1);
    }
    fscanf(file_ptr, "%lf", matching_val);

    fscanf(file_ptr, "%d", num_of_pics);
    *pic_arr = read_pictures(file_ptr, *num_of_pics);

    fscanf(file_ptr, "%d", num_of_objs);
    *obj_arr = read_objects(file_ptr, *num_of_objs);

    fclose(file_ptr);
}

int coord_to_index(int row, int col, int row_size) {
    return row * row_size + col;
}
