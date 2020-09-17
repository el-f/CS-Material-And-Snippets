import collections
import string


def main():
    d = collections.deque(string.ascii_lowercase)
    print("item count:", str(len(d)))

    for elem in d:
        print(elem.upper(), end=",")

    d.pop()
    d.popleft()
    d.append(2)
    d.appendleft(3)
    print("\n")
    print(d)
    d.rotate(2)
    print(d)


if __name__ == '__main__':
    main()
