#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcs8.h"
#include "employee.h"

void printArr(void *arr, int size, int typeSize, void (*print)(void *)) {
    for (int i = 0; i < size; i++) {
        print((char *) arr + i * typeSize);
        printf("%s", (i == size - 1 ? " " : ", "));
    }
    printf("\n");
}

int main() {
    //Q1
    printf("%zu\n", sum("wow", getAsciiSum));
    printf("%zu\n", sum("wow", strlen));

    //Q2
    Employee employees[5] = {
            {"idiot",   8000,   1},
            {"moron",   19000,  5},
            {"lol",     420000, 10},
            {"wow",     1337,   6},
            {"kokoman", 7777,   3}
    };
    qsort(employees, 5, sizeof(Employee), compareEmployeesBySalary);
    printArr(employees, 5, sizeof(Employee), printEmployee);

    qsort(employees, 5, sizeof(Employee), compareEmployeesBySeniority);
    printArr(employees, 5, sizeof(Employee), printEmployee);

    Employee search = {"wow", 0, 0};
    Employee *emp = bsearch(&search, employees, 5, sizeof(Employee), compareEmployeeByName);
    if (emp) printEmployee(emp);
    else printf("not found\n");
    printf("\n");

    Employee search2 = {"NOT HERE", 0, 0};
    Employee *emp2 = bsearch(&search2, employees, 5, sizeof(Employee), compareEmployeeByName);
    if (emp2) printEmployee(emp2);
    else printf("not found\n");
    printf("\n");

    system("pause");
}