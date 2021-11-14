from enum import Enum, unique, auto


@unique
class Fruit(Enum):
    APPLE = 1
    BANANA = 2
    ORANGE = 3
    TOMATO = 4
    RED_DELICIOUS = auto()
    PEAR = auto()


def main():
    print(Fruit.APPLE)
    print(type(Fruit.APPLE))
    print(repr(Fruit.APPLE))

    print(Fruit.APPLE.name, Fruit.APPLE.value)

    print(Fruit.PEAR.value, Fruit.RED_DELICIOUS.value)

    my_fruits = {}
    my_fruits[Fruit.BANANA] = "HELLO"
    print(my_fruits)
    print(my_fruits[Fruit.BANANA])


if __name__ == '__main__':
    main()
