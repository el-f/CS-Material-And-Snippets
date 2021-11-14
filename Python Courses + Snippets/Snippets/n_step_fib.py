def n_step_fib(n, m):
    out = [0, 1, 1][:m]
    while len(out) < m:
        x = 2 * out[-1]
        if len(out) > n:
            x -= out[-(n + 1)]
        out.append(x)
    return out


if __name__ == '__main__':
    for n in range(1, 11):
        print(f'{n}: {n_step_fib(n, 20)}')
