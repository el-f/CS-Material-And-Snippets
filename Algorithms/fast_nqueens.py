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
