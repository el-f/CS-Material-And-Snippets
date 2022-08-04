#ifndef UTILS_H_
#define UTILS_H_

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

typedef struct {
	int id;
	int size;
	int *matrix;
	int match_row;
	int match_col;
	int obj_id;
} Picture;

typedef struct {
	int id;
	int size;
	int *matrix;
} Object;

void read_from_file(double*, int*, int*, Picture**, Object**);
void write_to_file(int, int, int, int);
int coord_to_index(int /*row*/, int /*col*/, int /*row_size*/);

#endif /* UTILS_H_ */
