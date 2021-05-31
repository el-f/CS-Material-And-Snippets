import random
from functools import reduce


#
#  Author:          Elazar Fine
#  Python Version:  3.9.5
#


def pretty_exec(func):
    def wrapper():
        print(f'{func.__name__}:')
        func()
        print('---------------\n')

    return wrapper


@pretty_exec
def q1():
    def count_unique_type_lists(arr: list) -> int:
        return len(list(filter(lambda inner_list: len(set(map(type, inner_list))) >= 2, arr)))

    a = [
        [1, 5, 3],
        ['a', 'v', 3],
        ['sss', 'b'],
        [],
        [[3, 4, 5], ['a']],
        [(4, 5, 6), [4, 5, 6]]
    ]
    print(count_unique_type_lists(a))


@pretty_exec
def q2():
    vlst = ['x' + str(num) for num in range(10)]
    lamdic = {}
    for i, l in enumerate(vlst):
        lamdic[l] = lambda x, k=i: x * (k + 1)
    for v in vlst:
        for i in range(1, len(vlst) + 1):
            print(lamdic[v](i), end='\t')
        print()


@pretty_exec
def q3():
    class A:
        pass

        def __init__(self, y):
            self.y = y

        def __call__(self, z):
            if z > self.y:
                return z - self.y
            else:
                return self.y - z

    class B(A):
        def __call__(self, z=4):
            if z > self.y:
                return z - self.y
            else:
                return self.y - z

    print(A(5)(B(6)()))
    print(A(6)(B(5)(6)))


@pretty_exec
def q4():
    lst = [11, 3, 7, 8, 6, 2, 1, 2]

    # solution a:
    def sort(arr: list) -> list:
        return reduce(
            lambda a, b: [x for x in a if x <= b] + [b] + [x for x in a if x > b],
            arr,
            []
        )

    print(sort(lst))

    #######################
    # alternative solution (bubble sort):
    lst2 = [11, 3, 7, 8, 6, 2, 1, 2]

    def swap(arr: list, i: int, j: int):
        arr[i], arr[j] = arr[j], arr[i]

    def sort_alt(arr: list) -> list:
        for i in range(len(arr) - 1):
            for j in range(0, len(arr) - i - 1):
                if arr[j] > arr[j + 1]:
                    swap(arr, j, j + 1)
        return arr

    print(sort_alt(lst2))

    #######################
    # alternative solution (bubble sort with one loop):
    lst3 = [11, 3, 7, 8, 6, 2, 1, 2]

    def sortOneLoop(arr: list, *, i=0) -> list:
        while i < (len(arr) - 1):
            if arr[i] > arr[i + 1]:
                swap(arr, i, i + 1)
                i = -1
            i += 1
        return arr

    print(sortOneLoop(lst3))


class Q5A(object):
    # static vars
    decorator_calls = 0
    total_calls_count = 0

    def __init__(self, func):
        Q5A.decorator_calls += 1
        self.func = func
        self.func_calls_count = 0
        self.params_count = 0

    def __call__(self, *args, **kwargs):
        print(f'Number of decorator calls: ', self.decorator_calls)
        Q5A.total_calls_count += 1
        self.func_calls_count += 1
        self.params_count += len(args) + len(kwargs)
        print(f'\tNumber of calls ({self.func.__name__}): {self.func_calls_count}\n'
              f'\tNumber of parameters passed ({self.func.__name__}): {self.params_count}')
        print(f'\tTotal number of calls to all {Q5A.__name__} decorated funcs: {Q5A.total_calls_count}')

        return self.func(*args, **kwargs)


class Q5B:
    # static vars
    type_instances = {}
    decorator_calls = 0
    total_calls_count = 0

    def __init__(self, func):
        Q5B.decorator_calls += 1
        self.func = func
        self.func_calls_count = 0
        self.params_count = 0

    def __call__(self, *args, **kwargs):
        result = self.func(*args, **kwargs)
        t = type(result).__name__
        Q5B.type_instances.setdefault(t, 0)
        Q5B.type_instances[t] += 1

        Q5B.total_calls_count += 1
        self.func_calls_count += 1
        self.params_count += len(args) + len(kwargs)

        print(f'Number of decorator calls: ', Q5B.decorator_calls)
        print(f'\tNumber of calls ({self.func.__name__}): {self.func_calls_count}\n'
              f'\tNumber of parameters passed ({self.func.__name__}): {self.params_count}')
        print(f'\tTotal number of calls to all {Q5B.__name__} decorated funcs: {Q5A.total_calls_count}')

        for ret_type, occurrences_num in Q5B.type_instances.items():
            print(f'\t{ret_type} : {occurrences_num}')

        return result


@pretty_exec
def q5a():
    @Q5A
    def foo(a=list, b=5, c="hello"):
        _ = a, b, c
        return "nothing..."

    for _ in range(4):
        print(foo(["abc", "fds"]), end="\n\n")

    @Q5A
    def foo2(s):
        return 2 * s

    for _ in range(3):
        print(foo2("foo2 "), end="\n\n")

    @Q5A
    def foo3():
        pass

    foo3()


def rename(name):
    def dec(f):
        f.__name__ = name
        return f

    return dec


@pretty_exec
def q5b():
    types = [str, int, float, bytes, int, int, int]
    funcs = []

    for i, _ in enumerate(types):
        @Q5B
        @rename(f'f{i}')
        def f(x=i, y=''):
            _ = y
            return types[x](i)

        funcs.append(f)

    for f in funcs:
        # to see the call counter + type dict working non-
        # trivially we put some randomness here
        for i in range(random.randrange(0, 5)):
            if random.choice([True, False]):
                f()
            else:
                f(y="a param to increase count")


# Q5C +  Q6 + Q7 are in the other files


if __name__ == '__main__':
    # exec the tests
    q1()
    q2()
    q3()
    q4()
    q5a()
    q5b()
