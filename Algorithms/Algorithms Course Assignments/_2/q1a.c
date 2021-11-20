#include <stdio.h>
#include <string.h>

#define LEFT_ARROW '-'
#define UP_ARROW '|'
#define UP_LEFT_ARROW '\\'

void LCS_LENGTH(const char *x, int m, const char *y, int n) {
    int c[m + 1][n + 1];
    char b[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        c[i][0] = 0;
        b[i][0] = '0';
    }

    for (int j = 0; j <= n; j++) {
        c[0][j] = 0;
        b[0][j] = '0';
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = UP_LEFT_ARROW;
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = UP_ARROW;
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = LEFT_ARROW;
            }
        }
    }

    puts("Table C:");
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%d ", c[i][j]);
        }
        puts("");
    }

    puts("\nTable B");
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%c ", b[i][j]);
        }
        puts("");
    }
}

int main() {
    char *X = "1100101";
    char *Y = "101101110";
    LCS_LENGTH(X, (int) strlen(X), Y, (int) strlen(Y));
    return 1;
}
