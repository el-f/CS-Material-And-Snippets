import math


def most_significant_digit(n: int) -> int:
    k = math.log10(n)
    k = k - math.floor(k)
    return math.floor(math.pow(10, k))


if __name__ == '__main__':
    print(
        all((
            most_significant_digit(354) == 3,
            most_significant_digit(123) == 1,
            most_significant_digit(987) == 9,
        ))
    )
