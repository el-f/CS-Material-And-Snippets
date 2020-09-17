import random
import math


def length(n: int):
    return int(math.log10(n)) + 1


def quickselect_median(n, pivot_fn=random.choice):
    if length(n) % 2 == 1:
        return quickselect(n, length(n) / 2, pivot_fn)
    else:
        return 0.5 * (quickselect(n, length(n) / 2 - 1, pivot_fn) +
                      quickselect(n, length(n) / 2, pivot_fn))


def quickselect(n, k, pivot_fn):
    """
    Select the kth element in l (0 based)
    :param n: List of numerics
    :param k: Index
    :param pivot_fn: Function to choose a pivot, defaults to random.choice
    :return: The kth element of l
    """
    if length(n) == 1:
        assert k == 0
        return n[0]

    pivot = pivot_fn(n)

    lows = [el for el in n if el < pivot]
    highs = [el for el in n if el > pivot]
    pivots = [el for el in n if el == pivot]

    if k < length(lows):
        return quickselect(lows, k, pivot_fn)
    elif k < length(lows) + length(pivots):
        # We got lucky and guessed the median
        return pivots[0]
    else:
        return quickselect(highs, k - length(lows) - length(pivots), pivot_fn)
