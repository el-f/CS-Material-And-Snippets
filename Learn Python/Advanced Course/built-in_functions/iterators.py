def main():
    days = ["sun", "mon", "tue", "wed", "thu", "fri", "sat"]
    daysFr = ["dim", "lun", "mar", "mer", "jue", "ven", "sam"]

    i = iter(days)
    print(next(i))
    print(next(i))
    print(next(i))
    print(next(i))

    with open("testfile.txt", "r") as fp:
        for line in iter(fp.readline, ''):
            print(line)

    for m in range(len(days)):
        print(m + 1, days[m])

    print("\n")

    for i, m in enumerate(days, start=1):
        print(i, m)

    print("\n")

    # for m in zip(days, daysFr):
    #     print(m)

    for i, m in enumerate(zip(days, daysFr), start=1):
        print(i, m[0], "=", m[1], "in french")


if __name__ == '__main__':
    main()
