#include <stdio.h>

# define STR_LEN 9

void print_matrix(int *mat, int n, int w) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < w; j++) {
            printf("%4d", *mat++);
        }
        puts("");
    }
    puts("");
}

int get_val(const int *arr, int row, int col, int row_size) {
    return *(arr + row * row_size + col);
}

void q4(int *values, int K, int N, char *types) {
    int F[K + 1][N + 1];
    int X[K + 1][N + 1];

    for (int i = 0; i < K + 1; i++) {
        for (int j = 0; j < N + 1; j++) {
            F[i][j] = 0;
            X[i][j] = 0;
        }
    }

    int cell_value, mixed_value, last_total;

    for (int t = 1; t < K + 1; t++) {       // t for type
        for (int n = 1; n < N + 1; n++) {   // n of number
            last_total = mixed_value = 0;

            // current cell_value of this cell
            cell_value = get_val(values, t - 1, n, N + 1);
            if (t > 1) {
                if (n > 1) {
                    /*
                     * total cell_value of prev num of current type
                     *  + total cell_value remaining last type
                     */
                    mixed_value = get_val(values, t - 1, X[t][n - 1], N + 1)
                                  + F[t - 1][n - X[t][n - 1]];
                }
                // current total cell value for same number of buildings of all last types
                last_total = F[t - 1][n];
            }
            if (last_total > cell_value && last_total >= mixed_value) {
                F[t][n] = last_total;
                X[t][n] = 0;
            } else if (cell_value >= mixed_value && cell_value >= last_total) {
                F[t][n] = cell_value;
                X[t][n] = n;
            } else if (mixed_value > cell_value && mixed_value > last_total) {
                F[t][n] = mixed_value;
                X[t][n] = X[t][n - 1];
            }
        }
    }

    puts("\nF Table:");
    print_matrix((int *) F, K + 1, N + 1);
    puts("X Table:");
    print_matrix((int *) X, K + 1, N + 1);

    printf("\nOptimal Solution: %d\n", F[K][N]);
    for (int k = K, t = k - 1, n = N, b_num; k > 0 && n > 0;
         k -= b_num, n -= b_num, t -= (b_num - 1)) {
        b_num = X[k][n];
        printf("\t%d %s\n", b_num, types + t * STR_LEN);
    }
}

int main() {
    char types[][STR_LEN] = {
            "Megurim",
            "Mishar",
            "Misradim",
            "Melonaut"
    };
    int values[][6] = {
            {0, 2, 4,  6,  8,  10},
            {0, 6, 9,  9,  10, 11},
            {0, 1, 1,  2,  3,  15},
            {0, 8, 12, 20, 16, 12}
    };
    int K = 4;
    int N = 5;

    puts("");
    q4((int *) values, K, N, (char *) types);
    puts("\n");
}
