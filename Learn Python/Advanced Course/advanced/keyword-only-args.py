def main():
    func(1, 2, suppress_exceptions=True)
    func(1, 2)
    # func(1, 2, True)  # wont run


def func(arg1, arg2, *, suppress_exceptions=False):
    pass


if __name__ == '__main__':
    main()
