def myFunc(arg1, arg2=None):
    """
    myFunc(arg1, arg2=none) --> just prints the args
    :param arg1: first argument
    :param arg2: second argument defaults to none
    :return: void
    """
    print(arg1, arg2)


def main():
    print(myFunc.__doc__)


if __name__ == '__main__':
    main()
