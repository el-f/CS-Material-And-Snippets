
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "exe.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error in params\n");
        system("pause");
        return -1;

    }

    int opt;
    sscanf(argv[1], "%d", &opt);
    if (opt == 1)
        Q1();
    else if (opt == 2)
        Q2();
    else {
        printf("Error in params\n");
        system("pause");
        return -2;
    }

    system("pause");
    return 1;

}
