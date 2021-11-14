#ifndef FAMILY
#define FAMILY

typedef struct {
    char *name;
    int numOfPeople;
} Family;

int initFamily(Family *pFamily);

void printFamily(const Family *pFamily);

void freeFamily(Family *pFamily);

#endif //LAB7_FAMILY_H
