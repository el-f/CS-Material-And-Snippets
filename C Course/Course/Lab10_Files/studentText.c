#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include "student.h"


void writeStudentToTextFile(FILE *fp, Student *st) {
    fprintf(fp, "%s\t%d\t%.2f\n", st->name, st->id, st->avg);

}

int readStudentFromTextFile(FILE *fp, Student *st) {
    char temp[255];
    if (fscanf(fp, "%s %d %f", temp, &st->id, &st->avg) != 3)
        return 0;
    st->name = _strdup(temp);
    return 1;
}

int writeStudentArrToTextFile(const char *fileName, Student *stArr, int count) {
    FILE *fp;
    fp = fopen(fileName, "w");
    if (!fp)
        return 0;
    fprintf(fp, "%d\n", count);

    for (int i = 0; i < count; i++)
        writeStudentToTextFile(fp, &stArr[i]);


    fclose(fp);
    return 1;
}


Student *readStudentArrFromTextFile(const char *fileName, int *pCount) {
    Student *arr = NULL;
    FILE *fp = fopen(fileName, "r");
    if (!fp)
        return NULL;
    fscanf(fp, "%d", pCount);
    arr = (Student *) malloc(*pCount * sizeof(Student));
    if (!arr) {
        fclose(fp);
        return NULL;
    }
    for (int i = 0; i < *pCount; i++) {
        if (!readStudentFromTextFile(fp, &arr[i])) {
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
void addStudentToEndOfTextFile(const char *fileName) {
    int count;
    FILE *fp;
    Student st;

    initStudent(&st);

    fp = fopen(fileName, "r+");
    if (!fp)
        return;
    fseek(fp, 0, SEEK_SET);
    fscanf(fp, "%d", &count);
    fseek(fp, 0, SEEK_END);
    writeStudentToTextFile(fp, &st);
    count++;
    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "%d", count);
    fclose(fp);
}


