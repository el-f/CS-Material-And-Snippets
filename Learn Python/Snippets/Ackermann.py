def A(m, n):
    if m == 0:
        ans = n + 1
    elif n == 0:
        ans = A(m - 1, 1)
    else:
        ans = A(m - 1, A(m, n - 1))
    return ans


def main():
    for m in range(4):
        for n in range(5):
            print("A(", m, ",", n, ") = ", A(m, n))


if __name__ == '__main__':
    main()
