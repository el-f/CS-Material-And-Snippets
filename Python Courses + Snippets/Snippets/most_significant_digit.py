import math


def most_significant_digit(n: int) -> int:
    k = math.log10(n)
    k = k - math.floor(k)
    return math.floor(math.pow(10, k))


# same thing but we call the division explicitly 10^(a-b) = 10^a/10^b
def most_significant_digit_2(n: int) -> int:
    return n // 10 ** math.floor(math.log10(n))


if __name__ == '__main__':
    print(
        all((
            most_significant_digit(354) == 3,
            most_significant_digit(123) == 1,
            most_significant_digit(987) == 9,

            most_significant_digit_2(354) == 3,
            most_significant_digit_2(123) == 1,
            most_significant_digit_2(987) == 9,
        ))
    )
