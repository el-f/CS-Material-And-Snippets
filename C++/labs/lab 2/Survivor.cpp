//
// Created by Elazar on 22/02/2022.
//

#include "Survivor.h"
#include <string.h>
#include <iostream>

using namespace std;

void Survivor::init(char *_name, int _age)
{
    strcpy(name, _name);
    age = _age;
}

void Survivor::print()
{
    cout << "name: " << name << ", age: " << age << endl;
}

const char *Survivor::getName() const
{
    return name;
}

int Survivor::getAge() const
{
    return age;
}

void init_survivor(Survivor &s)
{
    char name[20];
    int age;
    cout << "Enter survivor name:";
    cin >> name;
    cout << "Enter age:";
    cin >> age;
    s.init(name, age);
}
