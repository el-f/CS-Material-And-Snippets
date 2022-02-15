#include <iostream>

using namespace std;

struct Survivor
{
    char name[20];
    uint16_t age;
};

void init_survivor(Survivor &s)
{
    cout << "Enter name:";
    cin >> s.name;
    cout << "Enter age:";
    cin >> s.age;
}

void print_survivor(Survivor &s)
{
    cout << "Name: " << s.name << " | Age: " << s.age << endl;
}

struct Tribe
{
    uint16_t MAX_SURVIVORS;
    uint16_t survivors_count;
    Survivor **survivors;
};

void init_tribe(Tribe &t, uint16_t max_survivors)
{
    t.MAX_SURVIVORS = max_survivors;
    t.survivors_count = 0;
    t.survivors = new Survivor*[t.MAX_SURVIVORS];
}

void init_tribe(Tribe &t)
{
    uint16_t ms;
    cout << "Enter max survivors:";
    cin >> ms;
    init_tribe(t, ms);
}


void print_tribe(Tribe &t)
{
    for (uint16_t s = 0; s < t.survivors_count; s++)
        print_survivor(*t.survivors[s]);
}

void add_survivor(Tribe &t)
{
    if (t.survivors_count >= t.MAX_SURVIVORS)
    {
        cout << "The tribe is full!" << endl;
        return;
    }
    t.survivors[t.survivors_count] = new Survivor;
    init_survivor(*t.survivors[t.survivors_count]);
    t.survivors_count++;
}

void free_tribe(Tribe &t)
{
    for (int i = 0; i < t.survivors_count; i++) {
        delete t.survivors[i];
    }
    delete[] t.survivors;
}

void part1()
{
    Survivor survivor{};
    init_survivor(survivor);
    print_survivor(survivor);
}

void part2()
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
            print_survivor(*tribes[c][s]);

    for (uint8_t t = 0; t < 2; t++) delete[] *tribes[t];
}

void part3()
{
    uint16_t max_survivors_count;
    cout << "How many survivors in each tribe?";
    cin >> max_survivors_count;

    Tribe tribes[2];
    for (auto &tribe: tribes)
        init_tribe(tribe, max_survivors_count);

    for (auto &tribe: tribes)
    {
        add_survivor(tribe);
        cout << "continue? [y/n]";
        char in;
        cin >> in;
        if (in != 'y') goto cont;
    }
    cont:
    for (auto &tribe: tribes) print_tribe(tribe);
    for (auto &tribe: tribes) free_tribe(tribe);
}

int main()
{
//    part1();
//    part2();
    part3();
}
