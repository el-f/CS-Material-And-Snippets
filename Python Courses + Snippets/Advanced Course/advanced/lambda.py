def main():
    ctemps = [0, 12, 34, 100]
    ftemps = [32, 65, 100, 212]

    # regular way
    print(list(map(c_to_f, ctemps)))
    print(list(map(f_to_c, ftemps)))

    # lambda way
    print(list(map(lambda t: (t * 9 / 5) + 32, ctemps)))
    print(list(map(lambda t: (t - 32) * 5 / 9, ftemps)))


def c_to_f(temp):
    return (temp * 9 / 5) + 32


def f_to_c(temp):
    return (temp - 32) * 5 / 9


if __name__ == '__main__':
    main()
