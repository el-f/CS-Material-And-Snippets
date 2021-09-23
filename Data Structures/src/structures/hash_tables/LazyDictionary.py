from collections.abc import Mapping


class LazyDict(Mapping):
    def __init__(self, *args, **kw):
        self._raw_dict = dict(*args, **kw)

    def __getitem__(self, key):
        func, arg = self._raw_dict.__getitem__(key)
        return func(arg)

    def __iter__(self):
        return iter(self._raw_dict)

    def __len__(self):
        return len(self._raw_dict)


# a version caching the results to avoid recomputing
class CachedLazyDict(dict):
    def __getitem__(self, item):
        value = dict.__getitem__(self, item)
        if not isinstance(value, int):
            function, arg = value
            value = function(arg)
            dict.__setitem__(self, item, value)
        return value


def expensive_to_compute(arg):
    return arg ** 0.00000333


if __name__ == '__main__':

    calculations = LazyDict(
        {
            'expensive1': (expensive_to_compute, 0.5),
            'expensive2': (expensive_to_compute, 2),
        }
    )
    print(calculations['expensive1'])
    print(calculations['expensive2'])

    calculations2 = CachedLazyDict(
        {
            'expensive1': (expensive_to_compute, 0.5),
            'expensive2': (expensive_to_compute, 2),
        }
    )
    print(calculations2['expensive1'])
    print(calculations2['expensive2'])
