import functools
import itertools
import operator
import random
import time


def flatten_with_append(lst: list[list]) -> list:
    flat = []
    for il in lst:
        for x in il:
            flat.append(x)
    return flat


def flatten_with_extend(lst: list[list]) -> list:
    flat = []
    for il in lst:
        flat.extend(il)
    return flat


def flatten_with_plus(lst: list[list]) -> list:
    flat = []
    for il in lst:
        flat += il
    return flat


def flatten_with_l_comp(lst: list[list]) -> list:
    return [x for il in lst for x in il]


def flatten_with_chain(lst: list[list]) -> list:
    return list(itertools.chain.from_iterable(lst))


def flatten_with_reduce(lst: list[list]) -> list:
    return functools.reduce(operator.iconcat, lst, [])
    # +=


def flatten_with_sum(lst: list[list]) -> list:
    return sum(lst, [])


def time_f(f):
    elapsed = 0.0
    n = 100
    M = 1000
    N = 100
    for _ in range(n):
        lst = [[random.randint(0, 1000000) for _ in range(N)] for __ in range(M)]
        start = time.perf_counter()
        f(lst)
        elapsed += time.perf_counter() - start

    # bit of extra fluff for nice & indented output
    fn = f.__name__
    print(fn, ' ' * (6 - len(fn.partition('h_')[2])), '\t\t', "%.6f ms" % (elapsed / n * 1000))


if __name__ == '__main__':
    time_f(flatten_with_append)
    time_f(flatten_with_extend)
    time_f(flatten_with_plus)
    time_f(flatten_with_l_comp)
    time_f(flatten_with_chain)
    time_f(flatten_with_reduce)
    time_f(flatten_with_sum)
