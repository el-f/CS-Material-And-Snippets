#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "exe.h"
#include "DateTime.h"
#include "macros.h"

void Q1() {
    Date birthdate = {1, 2, 1977, {5, 4, 3}, "Archer"};

    printDate(&birthdate);

}

void Q2() {
    int i;
    int x = 6;
    int y = 7;
    int arr[5] = {1, 2, 3, 4, 5};

    printf("\n\nHalf of %d is %d\n", x, HALFOF(x));
    printf("The avg of: ");
    for (i = 0; i < 5; i++)
        printf(" %d ", arr[i]);
    printf("is %f \n", AVG5(arr[0], arr[1], arr[2], arr[3], arr[4]));
    printf("%d  + %d   = %d \n", x, y, SUM(x, y));
    printf("The max of %d and %d is:  %d \n", x, y, MAX(x, y));
    printf("The min of %d and %d is:  %d \n", x, y, MIN(x, y));

    printf("The square of %d+%d is:  %d \n", x, y, SQUARE(SUM(x, y)));

    PRINT(hello\n\n);

}

