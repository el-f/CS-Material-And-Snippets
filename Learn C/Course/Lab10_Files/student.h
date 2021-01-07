#pragma once

#include <stdio.h>

typedef struct {
    char *name;
    int id;
    float avg;
} Student;


void showStudent(Student *st);

void initStudent(Student *st);

void showStudentArr(Student *st, int count);

void freeStudentArr(Student *stArr, int count);
