def main():
    evens = [2, 4, 6, 8, 10, 12, 14, 16]

    print(list(map(
        lambda e: e ** 2,
        filter(lambda e: 4 < e < 16, evens)
    )))

    print([e ** 2 for e in evens if 4 < e < 16])


if __name__ == '__main__':
    main()
