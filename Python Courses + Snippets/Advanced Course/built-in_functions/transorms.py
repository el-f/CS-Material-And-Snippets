def main():
    nums = (1, 8, 4, 5, 13, 26, 381, 213, 222)
    chars = "abcDefGhiJklM"
    grades = (91, 50, 61, 60, 100, 21, 85, 77)

    odds = list(filter(filterfunc, nums))
    print(odds)

    lowers = list(filter(filterfunc2, chars))
    print(lowers)

    squares = list(map(squaresfunc, nums))
    print(squares)

    grades = sorted(grades)
    letters = list(map(tograde, grades))
    print(letters)


def filterfunc(x):
    if x % 2 == 0:
        return True
    return False


def filterfunc2(x):
    if x.isupper():
        return False
    return True


def squaresfunc(x):
    return x ** 2


def tograde(x):
    if x >= 90:
        return "A"
    elif 80 <= x < 90:
        return "B"
    elif 70 <= x < 80:
        return "C"
    elif 60 <= x < 70:
        return "D"
    return "F"


if __name__ == '__main__':
    main()
