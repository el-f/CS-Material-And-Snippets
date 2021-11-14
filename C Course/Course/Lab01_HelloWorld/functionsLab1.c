#include <stdio.h>
#include "functionsLab1.h"

void helloWorld() {
    printf("Hello World!\n");
}

void printTriangle(int basis) {
    for (int i = 1; i <= basis; i++) {
        for (int j = basis - i; j >= 0; j--) {
            printf(" ");
        }

        for (int j = 1; j <= i; j++) {
            printf("*");
        }

        printf("\n");
    }
}
