#include <stdio.h>
#include <minmax.h>

void print_matrix(int *mat, int n, int w, int is_chars) {
    char *ch_mat = (char *) mat;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < w; j++) {
            if (is_chars)   printf("%3c", *ch_mat++);
            else            printf("%5d", *mat++);
        }
        puts("");
    }
    puts("");
}

void print_x(int *X, int n) {
    printf("X Table:\nItem:\t");
    for (int i = 0; i < n; i++) printf("%5d", i + 1);
    printf("\nCount:\t");
    for (int i = 0; i < n; i++) printf("%5d", X[i]);
    puts("");
}

void q3e(int N, int *values, int *weights, int W) {
    int T[N + 1][W + 1];
    char S[N + 1][W + 1];
    int X[N];

    for (int i = 0; i < N + 1; i++) {
        for (int j = 0; j < W + 1; j++) {
            T[i][j] = 0;
            S[i][j] = '0';
        }
        X[i % N] = 0;
    }

    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < W + 1; j++) {
            if (weights[i - 1] <= j) {
                T[i][j] = max(T[i - 1][j],
                              T[i][j - weights[i - 1]] + values[i - 1]);
                if (T[i][j] != T[i - 1][j]) {
                    X[i - 1]++;
                    S[i][j] = 'y';
                } else {
                    S[i][j] = 'n';
                }
            } else {
                T[i][j] = T[i - 1][j];
                S[i][j] = 'n';
            }
        }
    }

    puts("T Table:");
    print_matrix((int *) T, N + 1, W + 1, 0);
    puts("S Table:");
    print_matrix((int *) S, N + 1, W + 1, 1);
    print_x(X, N);

    printf("\nOptimal Solution: %d\n", T[N][W]);
    for (int n = N, w = W; n > 0; n--) {
        if (T[n][w] != T[n - 1][w]) {
            printf("\tItem #%d | Weight = %d | Value = %d\n", n,
                   weights[n - 1], values[n - 1]);
            w -= weights[n - 1];
        }
    }
}

int main() {
    int values[] = {16, 32, 56, 28, 30};
    int weights[] = {1, 4, 5, 2, 4};
    int W = 11;
    int N = sizeof(values) / sizeof(values[0]);
    q3e(N, values, weights, W);
}