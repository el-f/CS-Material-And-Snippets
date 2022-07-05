def build_board(n, diags):
    return [diags[i % 2] + (i // 2) for i in range(n)]


def n_queens_mod6_eq_2(n):
    board = build_board(n, [0, n // 2])
    board[n - 1], board[n // 2 - 1] = board[n // 2 - 1], board[n - 1]
    board[0], board[n // 2] = board[n // 2], board[0]
    return board


def n_queens(n):
    if n == 1:                      return [0]
    if n == 2 or n == 3:            return []
    if n % 6 == 0 or n % 6 == 4:    return build_board(n, [n // 2, 0])
    if n % 6 == 1 or n % 6 == 5:    return build_board(n - 1, [n // 2, 0]) + [n - 1]
    if n % 6 == 2:                  return n_queens_mod6_eq_2(n)
    return n_queens_mod6_eq_2(n - 1) + [n - 1]


# ----------------------------------------------------------------------------------------------------------------------
# ****************************
# ********* Tests ************
# ****************************
# ----------------------------------------------------------------------------------------------------------------------


print("All tests")


def test_all():
    import random
    MAX_N = 1000

    def check(n):

        result = n_queens(n)
        if not isinstance(result, list):
            print("Not a valid array")
            return False

        lenOk = len(result) == (0 if n == 2 or n == 3 else n)
        if not lenOk:
            print(f"Invalid result length ({len(result)}) for n={n}")
            return False

        noatk = (-1, -1)
        cols = [None] * n
        ldiag = [None] * n * 2
        rdiag = [None] * n * 2

        for row, col in enumerate(result):
            if not (0 <= col < n):
                print(f"Queen at row {row}, col {col} is outside bounds")
                return False

            atk = cols[col] or ldiag[col + row] or rdiag[col - row + n - 1] or noatk
            if atk is not noatk:
                print(f"Queen at row={row}, col={col} can be attacked by queen at row={atk[0]}, col={atk[1]}")
                return False
            cols[col] = ldiag[col + row] = rdiag[col - row + n - 1] = (row, col)
        return True

    def test_for(n):
        print(f"{n:04} : PASSED" if check(n) else "FAILED")

    print(f"Tests for n=1 to {MAX_N}")
    test_cases = list(range(1, MAX_N + 1))
    # random.shuffle(test_cases)
    for n in test_cases:
        test_for(n)


if __name__ == '__main__':
    test_all()
