#include <stdio.h>
#include "Person.h"

const char *typeToString[NUM_OF_TYPES] = {
        "Man", "Woman", "Boy", "Girl"
};

void printPerson(const Person *person) {
    printf("Person: %s (%s) ", person->name, typeToString[person->type]);
    printAddress((const Address *) &person->address);
}

void initPerson(Person *person) {
    printf("Please enter name:");
    scanf("%s", person->name);

    person->type = getTypeFromUser();

    initAddress(&person->address);
}

PersonType getTypeFromUser() {
    printf("Please Select type of person:\n");
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        printf("%d) %s\n", i + 1, typeToString[i]);
    }
    int choice;
    scanf("%d", &choice);
    return choice - 1;
}


void initPeople(Person *person, int size) {
    for (int i = 0; i < size; i++) {
        printf("Fill The Details For Person #%d:\n", i + 1);
        initPerson(&person[i]);
        printf("\n");
    }
}

void printPeople(const Person *person, int size) {
    for (int i = 0; i < size; i++) {
        printPerson(&person[i]);
    }
}

