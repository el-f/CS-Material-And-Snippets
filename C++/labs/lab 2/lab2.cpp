#include <iostream>
#include "Survivor.h"
#include "Tribe.h"

using namespace std;

void part1()
{
    uint16_t survivors_count;
    cout << "How many survivors in each tribe?";
    cin >> survivors_count;

    Survivor *tribes[2][survivors_count];
    uint16_t count = 0;

    for (uint8_t t = 0; t < 2; t++)
    {
        *tribes[t] = new Survivor[survivors_count];
        for (uint16_t s = 0; s < survivors_count; s++)
        {
            tribes[t][s] = new Survivor();
            init_survivor(*tribes[t][s]);
            count++;
            cout << "continue? [y/n]";
            char in;
            cin >> in;
            if (in != 'y') goto cont;
        }
    }
    cont:
    for (uint8_t c = 0; c < 2; c++)
        for (uint16_t s = 0; s < survivors_count && survivors_count * c + s < count; s++)
            tribes[c][s]->print();

    for (uint8_t t = 0; t < 2; t++) delete[] *tribes[t];
}

void part2()
{
    uint16_t max_survivors_count;
    cout << "How many survivors in each tribe?";
    cin >> max_survivors_count;

    Tribe tribes[2];
    for (auto &tribe: tribes)
        init_tribe(tribe, max_survivors_count);

    for (auto &tribe: tribes)
    {
        cout << "Adding to tribe '" << tribe.getName() << "'..." << endl;
        while (tribe.getSurvivorsCount() < tribe.getMaxSurvivors())
        {
            tribe.add_survivor();
            cout << "continue? [y/n]";
            char in;
            cin >> in;
            if (in != 'y') goto cont;
        }
    }
    cont:
    for (auto &tribe: tribes) tribe.print();

    for (auto &tribe: tribes) remove_survivor(tribe);

    for (auto &tribe: tribes) tribe.print();

    for (auto &tribe: tribes) tribe.free_survivors();
}

int main()
{
//    part1();
    part2();
}
