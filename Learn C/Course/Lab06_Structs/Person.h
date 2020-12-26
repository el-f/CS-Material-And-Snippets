#ifndef PERSON_H_
#define PERSON_H_

#include "Address.h"

#define MAX_LEN 20

typedef enum {
    Man, Woman, Boy, Girl,
    NUM_OF_TYPES
} PersonType;

const char *typeToString[NUM_OF_TYPES];

typedef struct {
    char name[MAX_LEN];
    Address address;
    PersonType type;
} Person;

void initPerson(Person *person);

void printPerson(const Person *person);

void initPeople(Person *person, int size);

void printPeople(const Person *person, int size);

PersonType getTypeFromUser();

#endif /* PERSON_H_ */
