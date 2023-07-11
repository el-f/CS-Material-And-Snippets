is_valid_move = lambda x, y, n, visited: 0 <= x < n and 0 <= y < n and visited[x][y] == -1
deg = lambda x, y, n, visited: sum(1 for dx, dy in ((2, 1), (1, 2), (-1, 2), (-2, 1), (-2, -1), (-1, -2), (1, -2), (2, -1)) if is_valid_move(x + dx, y + dy, n, visited))

def knights_tour(start, n):
    visited = [[-1] * n for _ in range(n)]
    (x, y), path = start, [start]
    visited[x][y] = 0

    for move in range(1, n ** 2):
        moves = ((x + dx, y + dy)
                 for dx, dy in [(2, 1), (1, 2), (-1, 2), (-2, 1), (-2, -1), (-1, -2), (1, -2), (2, -1)]
                 if is_valid_move(x + dx, y + dy, n, visited))
        _, x, y = min((deg(nx, ny, n, visited), nx, ny) for nx, ny in moves) # Warnsdorrf's rule
        visited[x][y] = move
        path.append((x, y))
    return path