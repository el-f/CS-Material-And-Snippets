#pragma once
#include <stdio.h>
#include "student.h"

void writeStudentToTextFile(FILE* fp, Student* st);
int readStudentFromTextFile(FILE* fp, Student* st);
int writeStudentArrToTextFile(const char* fileName, Student* st, int count);
Student* readStudentArrFromTextFile(const char* fileName, int* pCount);
void addStudentToEndOfTextFile(const char* fileName);
