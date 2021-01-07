#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include "student.h"


int writeStudentToBFile(FILE *fp, Student *st) {
    int len = strlen(st->name);
    if (fwrite(&len, sizeof(int), 1, fp) != 1)
        return 0;
    if (fwrite(st->name, sizeof(char), (len + 1), fp) != (len + 1))
        return 0;
    if (fwrite(&st->id, sizeof(int), 1, fp) != 1)
        return 0;
    if (fwrite(&st->avg, sizeof(int), 1, fp) != 1)
        return 0;
    return 1;
}

int readStudentFromBFile(FILE *fp, Student *st) {
    int len;
    if (fread(&len, sizeof(int), 1, fp) != 1)
        return 0;
    st->name = (char *) malloc((len + 1) * sizeof(char));
    if (!st->name)
        return 0;
    if (fread(st->name, sizeof(char), (len + 1), fp) != (len + 1))
        return 0;
    if (fread(&st->id, sizeof(int), 1, fp) != 1)
        return 0;
    if (fread(&st->avg, sizeof(int), 1, fp) != 1)
        return 0;
    return 1;
}

int writeStudentArrToBFile(const char *fileName, Student *stArr, int count) {
    FILE *fp;
    fp = fopen(fileName, "wb");
    if (!fp)
        return 0;
    if (fwrite(&count, sizeof(int), 1, fp) != 1) {
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < count; i++) {
        if (!writeStudentToBFile(fp, &stArr[i])) {
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}


Student *readStudentArrFromBFile(const char *fileName, int *pCount) {
    Student *arr = NULL;
    FILE *fp = fopen(fileName, "rb");
    if (!fp)
        return NULL;
    fread(pCount, sizeof(int), 1, fp);
    arr = (Student *) malloc(*pCount * sizeof(Student));
    if (!arr) {
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < *pCount; i++) {
        if (!readStudentFromBFile(fp, &arr[i])) {
            fclose(fp);
            return NULL;
        }
    }
    fclose(fp);
    return arr;
}

//init student from user
//open file in read + write mode - binary
//seek to start
//read student count
//seek to end
//write student to file
//seek to start
//count++;
//write new count
//close file
void addStudentToEndOfBFile(const char *fileName) {
    int count;
    FILE *fp;
    Student st;

    initStudent(&st);

    fp = fopen(fileName, "r+b");
    if (!fp)
        return;
    fseek(fp, 0, SEEK_SET);
    fread(&count, sizeof(int), 1, fp);

    fseek(fp, 0, SEEK_END);
    writeStudentToBFile(fp, &st);
    count++;
    fseek(fp, 0, SEEK_SET);
    fwrite(&count, sizeof(int), 1, fp);
    fclose(fp);
}
