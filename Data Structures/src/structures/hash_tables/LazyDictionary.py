from collections.abc import Mapping
from typing import Callable


class LazyDict(Mapping):
    def __init__(self, *args, **kw):
        self._raw_dict = dict(*args, **kw)

    def __getitem__(self, key):
        func, arg = self._raw_dict[key]
        return func(arg)

    def __iter__(self):
        return iter(self._raw_dict)

    def __len__(self):
        return len(self._raw_dict)


# a version caching the results to avoid recomputing
class CachedLazyDict(dict):
    def __getitem__(self, item):
        # call explicitly to avoid using the overloaded function and recurse endlessly
        value = dict.__getitem__(self, item)
        if isinstance(value, tuple) and isinstance(value[0], Callable):
            function, arg = value
            value = function(arg)
            self[item] = value
        return value


def expensive_to_compute(arg):
    pow(1234567, 1234567)
    return 2 * arg


if __name__ == '__main__':

    calculations = LazyDict({
            'expensive1': (expensive_to_compute, 0.5),
            'expensive2': (expensive_to_compute, 2),
    })
    print(calculations['expensive1'])
    print(calculations['expensive2'])

    print("\n~~ cached dict testing:")
    calculations2 = CachedLazyDict({
            'expensive1': (expensive_to_compute, 0.5),
            'expensive2': (expensive_to_compute, 2),
    })
    print("first time calc results:")
    print(calculations2['expensive1'])
    print(calculations2['expensive2'])
    print("\ncached results:")
    print(calculations2['expensive1'])
    print(calculations2['expensive2'])
