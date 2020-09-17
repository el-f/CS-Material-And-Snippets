def addition(*args):
    result = 0
    for arg in args:
        result += arg
    return result


def main():
    print(addition(5, 10, 15, 20))
    print(addition(1, 2, 3))

    nums = [10, 20, 30, 40, 50, 60]
    print(addition(*nums))  # spread


if __name__ == '__main__':
    main()
