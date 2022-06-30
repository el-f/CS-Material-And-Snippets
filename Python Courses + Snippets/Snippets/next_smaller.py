from functools import reduce


def next_smaller(n):
    num = [int(i) for i in str(n)]
    if num == sorted(num):  return -1

    pos = len(num) - 2
    while pos >= 0 and num[pos + 1] >= num[pos]: pos -= 1

    nxt_smallest_right = pos + \
                         reduce(lambda a, b: b if a[1] < b[1] < num[pos] else a, enumerate(num[pos:]), (-1, -1))[0]
    num[pos], num[nxt_smallest_right] = num[nxt_smallest_right], num[pos]
    num = num[:pos + 1] + sorted(num[pos + 1:], reverse=True)

    s = ''.join(map(str, num))

    return int(s) if s[0] != '0' else -1


if __name__ == '__main__':
    cases = [(21, 12),
             (907, 790),
             (531, 513),
             (1027, -1),
             (441, 414),
             (123456798, 123456789),
             (513, 351),
             (351, 315),
             (315, 153),
             (153, 135),
             (135, -1),
             (100, -1),
             (2071, 2017),
             (1207, 1072),
             (414, 144),
             (123456789, -1),
             (29009, 20990),
             (1234567908, 1234567890),
             (9999999999, -1),
             (59884848483559, 59884848459853),
             (1023456789, -1),
             (51226262651257, 51226262627551),
             (202233445566, -1),
             (506789, -1)]
    for n, expected in cases:
        if next_smaller(n) != expected:
            print('FAIL: {} -> {}'.format(n, next_smaller(n)))
        else:
            print('PASS: {} -> {}'.format(n, next_smaller(n)))
