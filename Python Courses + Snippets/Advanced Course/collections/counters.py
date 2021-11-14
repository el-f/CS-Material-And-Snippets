from collections import Counter


def main():
    class1 = ["bob", "becky", "chad", "kevin", "jessica", "james", "melanie", "james"]
    class2 = ["bill", "becky", "frank", "kevin", "jessica", "sam", "melanie", "james"]

    c1 = Counter(class1)
    c2 = Counter(class2)

    print(c1["james"], "named james")

    print(sum(c1.values()), "students in class 1")

    c1.update(class2)

    print(sum(c1.values()), "students in class 1")

    print(c1.most_common(3))
    print(c1.most_common())

    print(c1.subtract(class2))
    print(c1.most_common(3))

    print(c1 & c2)


if __name__ == '__main__':
    main()
