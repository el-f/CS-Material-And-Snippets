#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "Student.h"
#include "MyMacros.h"

static const char *DegreeStr[eNofTypes] = {"First", "Second"};


int readStudentFromTxtFile(Student *pSt, FILE *fp) {
    if (fscanf(fp, "%d %d %d", &pSt->id, &pSt->type, &pSt->grade) != 3)
        return 0;
    return 1;
}

int saveStudentToBinaryFileCompressed(const Student *pSt, FILE *fp) {
    BYTE data[4] = {0};
    data[0] = pSt->id >> 16;
    data[1] = pSt->id >> 8;
    data[2] = pSt->id & 0xFF;
    data[3] = pSt->grade << 1 | pSt->type;

    if (fwrite(&data, sizeof(BYTE), 4, fp) != 4)
        return 0;

    return 1;
}

int readStudentFromBinaryFileCompressed(Student *pSt, FILE *fp) {
    BYTE data[4];
    if (fread(&data, sizeof(BYTE), 4, fp) != 4)
        return 0;
    pSt->id = data[0] << 16 | data[1] << 8 | data[2];
    pSt->grade = (data[3] >> 1) & 0x7F;
    pSt->type = data[3] & 0x1;

    return 1;
}

void showStudent(const Student *pSt) {
    printf("%d %s %d\n", pSt->id, DegreeStr[pSt->type], pSt->grade);
}