
# my solution for this kata: 55983863da40caa2c900004e

def parse_int(n: int) -> str:
    return "".join(sorted(str(n), reverse=True))


def next_bigger(number):
    biggest = parse_int(number)
    for i in range(number + 1, int(biggest) + 1):
        if parse_int(i) == biggest:
            return i


if __name__ == '__main__':
    print(next_bigger(709))
    print(next_bigger(790))
    print(next_bigger(907))
