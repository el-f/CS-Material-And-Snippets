import itertools


def main():
    seq1 = ["joe", "john", "mike"]
    cyc1 = itertools.cycle(seq1)
    print(next(cyc1))
    print(next(cyc1))
    print(next(cyc1))
    print(next(cyc1))
    print(next(cyc1))

    count1 = itertools.count(100, 10)
    print(next(count1))
    print(next(count1))
    print(next(count1))

    vals = [10, 20, 90, 40, 50, 60, 70]
    acc = itertools.accumulate(vals, max)
    print(list(acc))

    x = itertools.chain("ABCD", "1234")
    print(list(x))

    print(list(itertools.dropwhile(testFunc, vals)))
    print(list(itertools.takewhile(testFunc, vals)))


def testFunc(x):
    return x < 40


if __name__ == '__main__':
    main()
