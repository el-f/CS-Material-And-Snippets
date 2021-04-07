from functools import cache


# remember results from calculations made in this function
# speeds up runtime in a MAJOR way using more memory
# to see the difference run with and WITHOUT the decorator...

@cache
def fib(n: int):
    if n <= 0:
        raise ValueError("n must be positive")
    if n == 1 or n == 2:
        return 1
    return fib(n - 1) + fib(n - 2)


def main():
    for i in range(1, 401):
        print(i, fib(i))
    print("done!")


if __name__ == '__main__':
    main()
