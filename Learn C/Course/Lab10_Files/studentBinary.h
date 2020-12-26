#pragma once
#include <stdio.h>
#include "student.h"

int writeStudentToBFile(FILE* fp, Student* st);
int readStudentFromBFile(FILE* fp, Student* st);
int writeStudentArrToBFile(const char* fileName, Student* st, int count);
Student* readStudentArrFromBFile(const char* fileName, int* pCount);
void addStudentToEndOfBFile(const char* fileName);
