from functools import cache


# remember results from calculations made in this function
# speeds up runtime in a MAJOR way using more memory
# to see the difference run with and WITHOUT the decorator...

@cache
def fib(n):
    if n <= 1:
        return n
    return fib(n - 1) + fib(n - 2)


def main():
    for i in range(400):
        print(i, fib(i))
    print("done!")


if __name__ == '__main__':
    main()

