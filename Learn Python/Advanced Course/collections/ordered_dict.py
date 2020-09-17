from collections import OrderedDict


def main():
    sports_teams = [("royals", (18, 12)),
                    ("cardinals", (1, 10)),
                    ("dragons", (11, 2)),
                    ("jets", (6, 3)),
                    ("warriors", (15, 6)),
                    ("kings", (5, 6))]

    sorted_teams = sorted(sports_teams, key=lambda t: [1][0], reverse=True)
    teams = OrderedDict(sorted_teams)
    print(teams)

    tm, wl = teams.popitem(False)
    print("top team:", tm, wl)

    for i, team in enumerate(teams, start=1):
        print(i, team)
        if i == 4:
            break

    a = OrderedDict({"a": 1, "b": 2, "c": 3})
    b = {"a": 1, "c": 3, "b": 2}
    print(a == b)


if __name__ == '__main__':
    main()
