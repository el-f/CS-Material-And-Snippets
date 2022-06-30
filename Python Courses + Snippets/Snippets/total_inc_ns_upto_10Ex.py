from math import factorial as fact


def total_inc_dec(x):
    a, b, c = fact(x), fact(9), fact(x + 9)
    return (((x + 10) * c) // a // b // 10) + (c // a // b) - (10 * x) - 1
