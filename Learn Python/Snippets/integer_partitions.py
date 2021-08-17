def num_of_partitions(n):
    parts = [1] + [0] * n
    for i in range(1, n + 1):
        for j, x in enumerate(range(i, n + 1)):
            parts[x] += parts[j]
    return parts[n]


def get_partitions(n):
    a = [0 for i in range(n + 1)]
    k = 1
    y = n - 1
    while k != 0:
        x = a[k - 1] + 1
        k -= 1
        while 2 * x <= y:
            a[k] = x
            y -= x
            k += 1
        l = k + 1
        while x <= y:
            a[k] = x
            a[l] = y
            yield a[:k + 2]
            x += 1
            y -= 1
        a[k] = x + y
        y = x + y - 1
        yield a[:k + 1]


if __name__ == '__main__':
    print(num_of_partitions(5))
    print(list(get_partitions(5)))
