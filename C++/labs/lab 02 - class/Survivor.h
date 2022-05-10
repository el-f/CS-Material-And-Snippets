//
// Created by Elazar on 22/02/2022.
//

#ifndef LEARN_CPP_SURVIVOR_H
#define LEARN_CPP_SURVIVOR_H

#include <iostream>

using namespace std;

class Survivor
{
private:
    char name[20];
    int age;

public:
    void init(char *_name, int _age);

    void print();

    const char *getName() const;

    int getAge() const;
};

void init_survivor(Survivor &);

#endif //LEARN_CPP_SURVIVOR_H
