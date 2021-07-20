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
    # iconcat is +=


def flatten_with_sum(lst: list[list]) -> list:
    return sum(lst, [])


def time_f(f):
    elapsed = 0.0
    test_iters = 100
    outer_size = 1000
    inner_size = 100
    for _ in range(test_iters):
        lst = [[random.randint(0, 1000000) for _ in range(inner_size)] for __ in range(outer_size)]
        start = time.perf_counter()
        f(lst)
        elapsed += time.perf_counter() - start

    # bit of extra fluff for nice & indented output
    fn = f.__name__
    print(fn, ' ' * (6 - len(fn.partition('h_')[2])), '\t\t', "%.6f ms" % (elapsed / test_iters * 1000))


if __name__ == '__main__':
    fs = {
        flatten_with_append,
        flatten_with_extend,
        flatten_with_plus,
        flatten_with_l_comp,
        flatten_with_chain,
        flatten_with_reduce,
        flatten_with_sum
    }

    # test functionality first:
    test_inp = [[1, 2], [3], [4, 5, 6], [7, 8, 9, 10]]
    excepted = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    for func in fs:
        assert func(test_inp) == excepted

    # compare times:
    for func in fs:
        time_f(func)
