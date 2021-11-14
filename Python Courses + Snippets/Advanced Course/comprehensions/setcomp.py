def main():
    ctemps = [0, 12, 34, 100, 5, 10, 14, 10, 41, 30, 12, 2, 12, 18, 29, 23]
    ftemps1 = [(t * 9 / 5) + 32 for t in ctemps]
    ftemps2 = {(t * 9 / 5) + 32 for t in ctemps}
    print(ftemps1)
    print(ftemps2)

    s_temp = "the quick brown fox jumped over lazy dog"
    chars = {c.upper() for c in s_temp if c != ' '}
    print(chars)


if __name__ == '__main__':
    main()
