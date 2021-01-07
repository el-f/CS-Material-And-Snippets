#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "Person.h"

void Q1();

void Q2();

void Q3();

void main() {
    printf("\n------------ Q1 ------------ \n");
    Q1();
    printf("\n------------ Q2 ------------ \n");
    Q2();
    printf("\n------------ Q3 ------------ \n");
    Q3();
    system("pause");
}

void Q1() {

    float res = calcAverage(1, 2, 3, 4, -1);
    printf("avg = %.3f\n", res);


    res = calcAverage(1, 2, 3, 4, 5, 6, -1);
    printf("avg = %.3f\n", res);

}

void Q2() {
    char *longStr = combiningStrings("Good", "Morning", "This", "Is", "A", "Nice", "Day", NULL);
    puts(longStr);
    free(longStr);
}

void Q3() {
    int arr[] = {1, 2, 3, 4, 5};

    printf("\n------------ Array of ints ------------ \n");
    manipulateArray(arr, sizeof(arr) / sizeof(int), printArrInt, printSumArrInt, printMaxArrInt, NULL);

    printf("\n------------ Array of Persons ------------ \n");
    Person arrP[4] = {{23457, "Michael"},
                      {12121, "Yael"},
                      {99090, "Gil"},
                      {87878, "Shachar"}};
    manipulateArray(arrP, 4, printPersonArr, printPersonBiggestID, printPersonShortestName, NULL);
}
