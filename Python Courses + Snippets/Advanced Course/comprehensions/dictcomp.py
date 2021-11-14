def main():
    ctemps = [0, 12, 34, 100]

    temp_dict = {t: (t * 9 / 5) + 32 for t in ctemps if t < 100}
    print(temp_dict)
    print(temp_dict[12])

    team1 = {"jones": 24, "idiot": 18, "smith": 30}
    team2 = {"white": 12, "mack": 99, "pierce": 4}

    new_team = {k: v for team in (team1, team2)
                for k, v in team.items()}
    print(new_team)


if __name__ == '__main__':
    main()
