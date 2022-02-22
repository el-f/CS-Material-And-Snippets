//
// Created by Elazar on 22/02/2022.
//

#ifndef TRIBE_H
#define TRIBE_H

#include "Survivor.h"

class Tribe
{
private:
    char name[20];
    int max_survivors;
    int survivors_count;
    Survivor **survivors;

public:
    void init(char *_name, int _max_survivors);

    void add_survivor();

    void remove_survivor(char *_name);

    void print();

    void free_survivors();

    const char *getName() const;

    int getMaxSurvivors() const;

    int getSurvivorsCount() const;

    Survivor **getSurvivors() const;
};

void init_tribe(Tribe &, uint16_t);

void remove_survivor(Tribe &);

#endif //TRIBE_H


