#include "Tribe.h"
#include <string.h>
#include <iostream>


using namespace std;

void init_tribe(Tribe &t, uint16_t max_survivors)
{
    char name[20];
    cout << "Enter tribe name:";
    cin >> name;
    t.init(name, max_survivors);
}

void Tribe::init(char *_name, int _max_survivors)
{
    strcpy(name, _name);
    max_survivors = _max_survivors;
    survivors_count = 0;
    survivors = new Survivor *[max_survivors];
}

void Tribe::add_survivor()
{
    if (survivors_count >= max_survivors)
    {
        cout << "The tribe is full!" << endl;
        return;
    }
    survivors[survivors_count] = new Survivor();
    init_survivor(*survivors[survivors_count]);
    survivors_count++;
}

void remove_survivor(Tribe &t)
{
    char name[20];
    cout << "Enter name of survivor to remove from tribe '" << t.getName() << "':";
    cin >> name;
    t.remove_survivor(name);
}

void Tribe::remove_survivor(char *_name)
{
    for (int i = 0; i < survivors_count; i++)
    {
        if (strcmp(survivors[i]->getName(), _name) == 0)
        {
            delete survivors[i];
            for (int j = i; j < survivors_count; j++)
            {
                survivors[j] = survivors[j + 1];
            }
            survivors_count--;
            break;
        }
    }
}

void Tribe::print()
{
    for (int i = 0; i < survivors_count; i++)
        survivors[i]->print();
}

void Tribe::free_survivors()
{
    for (int i = 0; i < survivors_count; i++)
    {
        delete survivors[i];
    }
    delete[] survivors;
}

const char *Tribe::getName() const
{
    return name;
}

int Tribe::getMaxSurvivors() const
{
    return max_survivors;
}

int Tribe::getSurvivorsCount() const
{
    return survivors_count;
}

Survivor **Tribe::getSurvivors() const
{
    return survivors;
}
