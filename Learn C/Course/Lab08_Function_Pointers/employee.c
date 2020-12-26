//
// Created by Elazar on 08/12/2020.
//
#include <stdio.h>
#include <string.h>

#include "employee.h"

int compareEmployeesBySalary(const void *pE1, const void *pE2) {
    Employee *e1 = (Employee *) pE1;
    Employee *e2 = (Employee *) pE2;

    return e1->salary == e2->salary ? 0 : e1->salary > e2->salary ? 1 : -1;
}

int compareEmployeesBySeniority(const void *pE1, const void *pE2) {
    Employee *e1 = (Employee *) pE1;
    Employee *e2 = (Employee *) pE2;

    return e1->xp == e2->xp ? 0 : e1->xp > e2->xp ? 1 : -1;
}

int compareEmployeeByName(const void *pE1, const void *pE2) {
    return strcmp(((Employee *) pE1)->name, ((Employee *) pE2)->name);
}

void printEmployee(void *ep) {
    Employee *e = (Employee *) ep;
    printf("%s - %d$ - %dxp", e->name, e->salary, e->xp);
}