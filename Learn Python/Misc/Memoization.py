# Explicit Implementation.
# Decorator implementation is in: practical_decorators/cache_decorator.py

fib_cache = {}


def fibonacci(n: int):
    if n < 0:
        raise ValueError("n must be positive")

    # if value in cache, return it:
    if n in fib_cache:
        print(f"found value for {n}: {fib_cache[n]}")
        return fib_cache[n]

    # else, compute the value for n
    if n == 0:
        value = 0
    elif n == 1 or n == 2:
        value = 1
    else:
        print(f"not found value for {n}...computing f({n - 1}) + f({n - 2})")
        value = fibonacci(n - 1) + fibonacci(n - 2)

    # cache the value, then return it
    fib_cache[n] = value
    return value


if __name__ == '__main__':
    # for i in range(401):
    #     print(i, fibonacci(i))
    print(400, "=>", fibonacci(400))
    print("done!")
