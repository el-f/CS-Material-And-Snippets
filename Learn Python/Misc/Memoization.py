# Explicit Implementation.
# Decorator implementation is in: practical_decorators/cache_decorator.py

fib_cache = {}


def fibonacci(n: int):
    if n <= 0:
        raise ValueError("n must be positive")

    # if value in cache, return it:
    if n in fib_cache:
        return fib_cache[n]

    # else, compute the value for n
    if n == 1 or n == 2:
        value = 1
    else:
        value = fibonacci(n - 1) + fibonacci(n - 2)

    # cache the value, then return it
    fib_cache[n] = value
    return value


if __name__ == '__main__':
    for i in range(1, 401):
        print(i, fibonacci(i))
    print("done!")
