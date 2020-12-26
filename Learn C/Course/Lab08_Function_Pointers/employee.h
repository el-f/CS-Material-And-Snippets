//
// Created by Elazar on 08/12/2020.
//
#ifndef LAB08_EMPLOYEE
#define LAB08_EMPLOYEE

typedef struct {
    char name[64];
    int salary;
    int xp;
} Employee;

int compareEmployeesBySalary(const void *pE1, const void *pE2);

int compareEmployeesBySeniority(const void *pE1, const void *pE2);

int compareEmployeeByName(const void* pE1, const void* pE2);

void printEmployee(void *e);

#endif //LAB08_EMPLOYEE_H
