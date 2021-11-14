#ifndef PERSON_H_
#define PERSON_H_

#define MAX_LEN 20
typedef struct {
    int id;
    char name[MAX_LEN];
} Person;


void printPersonArr(const void *arr, int size);

void printPersonBiggestID(const void *arr, int size);

void printPersonShortestName(const void *arr, int size);

#endif /* PERSON_H_ */
