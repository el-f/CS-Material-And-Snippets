//
// Created by Elazar on 01/12/2020.
//

#include <stdio.h>
#include "family.h"
#include "funcs7B.h"

int initFamily(Family *pFamily) {
    printf("Please enter family name:\n");
    char *name = getStrAuto();
    if (name == NULL) return 0; // name malloc failed
    pFamily->name = name;

    printf("Please enter num of people:\n");
    pFamily->numOfPeople = scanInt();

    getchar(); // clean buffer
    return 1;
}

void printFamily(const Family *pFamily) {
    printf("Family %s has %d people\n", pFamily->name, pFamily->numOfPeople);
}

void freeFamily(Family *pFamily) {
    free(pFamily->name);
}