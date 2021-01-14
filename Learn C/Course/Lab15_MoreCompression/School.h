#pragma once

#include "Student.h"

typedef enum {
    text, binary
} eFileType;


typedef struct {
    int classCount;
    int countInClass;
    Student **studentArr;
} School;


int createSchoolFromFile(const char *fileName, School *pSchool, eFileType fileType);

int saveSchoolToBinaryFile(const char *fileName, const School *pSchool);

void showSchool(const School *pSchool);

void freeSchool(School *pSchool);

int readStudentsInfoFromFile(School *pSchool, FILE *fp, eFileType fileType);

void getCounts(FILE *fp, School *pSchool, eFileType fileType);
