#pragma once

typedef enum {
    first, second, eNofTypes
} eDegreeType;
static const char *DegreeStr[eNofTypes];

typedef struct {
    int id;
    eDegreeType type;
    int grade;
} Student;

int readStudentFromTxtFile(Student *pSt, FILE *fp);

int saveStudentToBinaryFileCompressed(const Student *pSt, FILE *fp);

int readStudentFromBinaryFileCompressed(Student *pSt, FILE *fp);

void showStudent(const Student *pSt);
