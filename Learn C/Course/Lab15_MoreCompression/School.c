#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "School.h"
#include "MyMacros.h"


int createSchoolFromFile(const char *fileName, School *pSchool, eFileType fileType) {
    FILE *fp;
    if (fileType == text)
        fp = fopen(fileName, "r");
    else
        fp = fopen(fileName, "rb");

    CHECK_RETURN_0(fp);

    getCounts(fp, pSchool, fileType);

    pSchool->studentArr = (Student **) malloc(pSchool->classCount * sizeof(Student *));
    CHECK_NULL_CLOSE_FILE_0(pSchool->studentArr, fp);

    for (int i = 0; i < pSchool->classCount; i++) {
        pSchool->studentArr[i] = (Student *) malloc(pSchool->countInClass * sizeof(Student));
        CHECK_NULL_CLOSE_FILE_0(pSchool->studentArr[i], fp);
    }

    int res = readStudentsInfoFromFile(pSchool, fp, fileType);

    fclose(fp);
    return res;
}

void getCounts(FILE *fp, School *pSchool, eFileType fileType) {
    if (fileType == text) {
        fscanf(fp, "%d %d", &pSchool->classCount, &pSchool->countInClass);
    } else {
        BYTE data[2];
        if (fread(data, sizeof(BYTE), 2, fp) != 2)
            return;
        pSchool->classCount = data[0] << 1 | data[1] >> 7;
        pSchool->countInClass = data[1] & 0x7F;
    }
}

int readStudentsInfoFromFile(School *pSchool, FILE *fp, eFileType fileType) {
    int res;
    for (int i = 0; i < pSchool->classCount; i++) {
        for (int j = 0; j < pSchool->countInClass; j++) {
            if (fileType == text)
                res = readStudentFromTxtFile(&pSchool->studentArr[i][j], fp);
            else
                res = readStudentFromBinaryFileCompressed(&pSchool->studentArr[i][j], fp);
            if (res == 0)
                return 0;
        }
    }
    return 1;
}

int saveSchoolToBinaryFile(const char *fileName, const School *pSchool) {
    FILE *fp;

    fp = fopen(fileName, "wb");
    CHECK_RETURN_0(fp);

    BYTE data[2];

    data[0] = pSchool->classCount >> 1;
    data[1] = pSchool->countInClass | (pSchool->classCount & 0x1) << 7;

    if (fwrite(data, sizeof(BYTE), 2, fp) != 2)
        return 0;

    for (int i = 0; i < pSchool->classCount; i++) {
        for (int j = 0; j < pSchool->countInClass; j++)
            saveStudentToBinaryFileCompressed(&pSchool->studentArr[i][j], fp);
    }

    fclose(fp);
    return 1;
}


void showSchool(const School *pSchool) {
    printf("School Data\n");
    printf("There are %d classes and %d students in each calss\n", pSchool->classCount,
           pSchool->countInClass);
    for (int i = 0; i < pSchool->classCount; i++) {
        printf("\n------ Class %d --------\n", (i + 1));
        for (int j = 0; j < pSchool->countInClass; j++)
            showStudent(&pSchool->studentArr[i][j]);
    }
}

void freeSchool(School *pSchool) {
    for (int i = 0; i < pSchool->classCount; i++)
        free(pSchool->studentArr[i]);
    pSchool->studentArr;
}