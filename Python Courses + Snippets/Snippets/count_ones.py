# sum bits in range(left, right + 1)
# solution for this kata: 596d34df24a04ee1e3000a25

def sum_up_to(n):
    if n == 0: return 0
    result, p, x = 0, 2, n

    while x > 0:
        result += (n // p) * (p >> 1)
        if (n & (p - 1)) > (p >> 1) - 1:
            result += (n & (p - 1)) - (p >> 1) + 1
        p <<= 1
        x >>= 1

    return result


def count_ones(left, right):
    return sum_up_to(right) - sum_up_to(left - 1)


if __name__ == '__main__':
    print(count_ones(0, int(1E9)))
