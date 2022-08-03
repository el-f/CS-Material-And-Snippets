import numpy as np
import heapq as hq


# each cell is a node, and each edge is a weight made up of the difference between the two cells
def shortest_path_weighted(grid):
    grid = grid.split("\n")
    n = len(grid)
    visited = np.ones((n, n)) * np.inf
    heap = [(0, 0, 0)]
    while heap:
        dist, x, y = hq.heappop(heap)
        if x == n - 1 and y == n - 1:
            return dist
        for i, j in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if 0 <= i < n and 0 <= j < n and \
                    (new_dist := dist + abs(int(grid[x][y]) - int(grid[i][j]))) < visited[i][j]:
                visited[i][j] = new_dist
                hq.heappush(heap, (new_dist, i, j))


# each cell is a node, and each edge is a weight of 1
# avoid the obstacles
def shortest_path(grid):
    grid = grid.split("\n")
    n = len(grid)
    visited = np.zeros((n, n))
    visited[0][0] = 1
    queue = [(0, 0, 0)]
    while queue:
        dist, x, y = hq.heappop(queue)
        if x == n - 1 and y == n - 1:
            return dist
        for i, j in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if 0 <= i < n and 0 <= j < n and grid[i][j] == '.' and visited[i][j] == 0:
                visited[i][j] = 1
                hq.heappush(queue, (dist + 1, i, j))
    return False


# each cell is a node, and each edge is a weight of 0
# avoid the obstacles
def is_there_a_path(grid):
    grid = grid.split("\n")
    w, h = len(grid[0]) - 1, len(grid) - 1
    Q = [(0, 0)]
    seen = set()

    def get_adj(r, c):
        for i, j in ((0, 1), (1, 0), (0, -1), (-1, 0)):
            if (0 <= r + i <= h) and (0 <= c + j <= w) and \
                    grid[r + i][c + j] != 'W' and (r + i, c + j) not in seen:
                Q.append((r + i, c + j))
                seen.add((r + i, c + j))

    while len(Q) > 0:
        y, x = Q.pop(0)
        if (y, x) == (h, w):
            return True
        get_adj(y, x)

    return False


from collections import defaultdict


# shortest path (by euclidean distance) with obstacles, return the grid with the path marked as "P"
def shortest_path_with_obstacles(grid):
    grid = [[c for c in row] for row in grid.split("\n")]
    n, m = len(grid), len(grid[0])
    visited = defaultdict(lambda: float('inf'))
    parent = {}

    S = next((i, j) for i in range(len(grid)) for j in range(len(grid[i])) if grid[i][j] == "S")  # Start
    G = next((i, j) for i in range(len(grid)) for j in range(len(grid[i])) if grid[i][j] == "G")  # Goal

    queue = [(0, S)]
    while queue:
        cost, (y, x) = hq.heappop(queue)

        if (y, x) == G:
            while (y, x) != S:
                y, x = parent[(y, x)]
                if (y, x) != S: grid[y][x] = "P"
            return "\n".join(''.join(row) for row in grid)

        for (dy, dx) in ((0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)):
            i, j = y + dy, x + dx
            new_cost = cost + (1 if abs(dy + dx) == 1 else 1.414)
            if 0 <= i < n and 0 <= j < m and new_cost < visited[(i, j)] and grid[i][j] != "X":
                visited[(i, j)] = new_cost
                hq.heappush(queue, (new_cost, (i, j)))
                parent[(i, j)] = (y, x)


dirs = {(1, 0): "up", (-1, 0): "down", (0, 1): "left",
        (0, -1): "right"}  # reversed for path reconstruction optimization.


# shortest path by node weight, return a list of directions
def cheapest_path(grid, finish, start):
    n, m = len(grid), len(grid[0])
    visited = defaultdict(lambda: float('inf'))
    queue = [(grid[start[0]][start[1]], start[0], start[1])]
    parent = {}
    while queue:
        cost, y, x = hq.heappop(queue)
        if (y, x) == finish:
            path = []
            curr = finish
            while curr != start:
                curr, dir = parent[curr]
                path.append(dir)
            return path

        for (dy, dx), dir in dirs.items():
            i, j = y + dy, x + dx
            if 0 <= i < n and 0 <= j < m and (new_cost := cost + grid[y][x]) < visited[(i, j)]:
                visited[(i, j)] = new_cost
                hq.heappush(queue, (new_cost, i, j))
                parent[(i, j)] = (y, x), dir


# cross grid from left to right with the minimal maximum costing node traversed. return list of path nodes.
# use multi-parameter cost. (max node in path, distance)
def best_path(grid):
    n, m = len(grid), len(grid[0])
    visited = defaultdict(lambda: (float('inf'), float('inf')))
    queue, parent = [], {}
    [hq.heappush(queue, (grid[i][0], 1, i, 0)) for i in range(n)]

    while queue:
        cost, dist, y, x = hq.heappop(queue)
        if x == m - 1:
            path = [(y, x)]
            while x != 0:
                y, x = parent[(y, x)]
                path.append((y, x))
            return path[::-1]

        for dy, dx in ((_dy, _dx) for _dy in range(-1, 2) for _dx in range(-1, 2)):
            i, j = y + dy, x + dx
            if 0 <= i < n and 0 <= j < m and ((new_cost := max(cost, grid[i][j])), dist + 1) < visited[(i, j)]:
                visited[(i, j)] = (new_cost, dist + 1)
                hq.heappush(queue, (new_cost, dist + 1, i, j))
                parent[(i, j)] = (y, x)


# ----------------------------------------------------------------------------------------------------------------------
# ****************************
# ********* Tests ************
# ****************************
# ----------------------------------------------------------------------------------------------------------------------


def assert_equals(actual, expected, message="FAILED"):
    if actual != expected:
        print(message)
        print("expected:", expected)
        print("actual:", actual)
        exit(1)


def expect(predicate, message):
    if not predicate:
        print(message)
        exit(1)


def describe(message):
    print(message)


def it(message):
    print(message)


def best_path_tests():
    describe('Fixed Tests')

    def verify(river, path, expected_depth, expected_length):
        assert_equals(path[0][1], 0, "Path does not start on left bank.")
        assert_equals(path[-1][1], len(river[0]) - 1, "Path does not end on right bank.")
        expect(
            all(abs(r - path[j][0]) <= 1 and abs(c - path[j][1]) <= 1 for j, (r, c) in enumerate(path[1:])),
            "Path is not continuous."
        )
        expect(
            max(river[r][c] for (r, c) in path) <= expected_depth,
            "Path is deeper than expected. Expected depth is %d." % expected_depth
        )
        expect(len(path) <= expected_length, "Path is longer than expected. Expected length is %d." % expected_length)
        print("~PASSED\n")

    it('Single cell')
    river = [[3]]
    path = best_path(river)
    verify(river, path, 3, 1)

    it('Single column')
    river = [
        [8],
        [8],
        [8],
        [8],
        [8],
        [8],
        [5],
        [8],
        [8],
        [8],
        [8],
        [8]]
    path = best_path(river)
    verify(river, path, 5, 1)

    it('Two columns')
    river = [
        [1, 8],
        [8, 8],
        [8, 8],
        [8, 1],
        [8, 8],
        [8, 8],
        [1, 8],
        [8, 1],
        [8, 8]]
    path = best_path(river)
    verify(river, path, 1, 2)

    it('Three columns')
    river = [
        [1, 8, 8],
        [8, 8, 8],
        [8, 8, 1],
        [8, 8, 1],
        [8, 1, 8],
        [8, 8, 1],
        [1, 1, 8],
        [8, 8, 1],
        [8, 8, 8]]
    path = best_path(river)
    verify(river, path, 1, 3)

    it('Three columns, long path')
    river = [
        [1, 8, 8],
        [8, 1, 8],
        [8, 1, 8],
        [8, 1, 8],
        [8, 1, 8],
        [8, 8, 1],
        [8, 1, 8],
        [8, 1, 1],
        [8, 8, 8]]
    path = best_path(river)
    verify(river, path, 1, 6)

    it('Three columns multiple paths')
    river = [
        [1, 8, 8],
        [8, 1, 8],
        [8, 1, 8],
        [8, 1, 8],
        [8, 1, 8],
        [8, 8, 1],
        [8, 1, 8],
        [8, 1, 1],
        [1, 8, 8]]
    path = best_path(river)
    verify(river, path, 1, 3)

    it('Four Columns')
    river = [
        [8, 8, 8, 8],
        [8, 8, 8, 8],
        [8, 8, 8, 8],
        [1, 1, 1, 8],
        [1, 8, 1, 8],
        [1, 8, 1, 8],
        [1, 8, 1, 8],
        [8, 8, 1, 8],
        [8, 8, 1, 1]]
    path = best_path(river)
    verify(river, path, 1, 7)

    it('Four Columns, flat river bed')
    river = [
        [1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1]]
    path = best_path(river)
    verify(river, path, 1, 4)

    it('Ten columns with loop')
    river = [
        [8, 8, 8, 8, 8, 8, 8, 8, 8, 8],
        [8, 8, 8, 8, 8, 8, 8, 8, 8, 8],
        [8, 8, 8, 8, 8, 8, 8, 8, 8, 8],
        [8, 8, 1, 1, 1, 1, 1, 1, 1, 1],
        [8, 8, 1, 8, 8, 8, 8, 8, 8, 8],
        [8, 8, 1, 1, 1, 8, 8, 8, 8, 8],
        [8, 8, 8, 8, 1, 8, 8, 8, 8, 8],
        [8, 8, 8, 8, 1, 8, 8, 8, 8, 8],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 8],
        [8, 8, 1, 8, 8, 8, 8, 8, 1, 8],
        [8, 8, 1, 8, 8, 8, 8, 8, 1, 8],
        [8, 8, 1, 1, 1, 1, 1, 1, 1, 8]]

    path = best_path(river)
    verify(river, path, 1, 15)

    it('Ten columns with multiple disjoint minimal depth paths')
    river = [
        [7, 7, 7, 7, 7, 7, 7, 7, 7, 7],
        [7, 7, 7, 7, 7, 7, 7, 7, 7, 7],
        [7, 5, 5, 5, 7, 7, 7, 7, 7, 7],
        [7, 5, 7, 5, 7, 7, 7, 7, 7, 7],
        [7, 5, 7, 5, 7, 7, 7, 7, 7, 7],
        [7, 5, 7, 5, 7, 7, 7, 7, 7, 7],
        [5, 5, 7, 5, 7, 7, 7, 7, 7, 7],
        [7, 7, 7, 5, 5, 5, 5, 5, 5, 5],
        [7, 7, 7, 7, 7, 7, 7, 7, 7, 7],
        [7, 7, 7, 7, 7, 7, 7, 7, 7, 7],
        [7, 7, 7, 7, 7, 7, 7, 7, 7, 7],
        [7, 7, 7, 7, 7, 7, 7, 7, 7, 7],
        [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],
        [7, 7, 7, 7, 7, 7, 7, 7, 7, 7]]

    path = best_path(river)
    verify(river, path, 5, 10)


def shortest_path_tests():
    describe("\nFixed tests:")
    a = "\n".join(
        [
            ".W...",
            ".W...",
            ".W.W.",
            "...W.",
            "...W."]
    )
    assert_equals(shortest_path(a[:]), 12)
    print("PASSED")
    a = "\n".join(
        [
            ".W...",
            ".W...",
            ".W.W.",
            "...WW",
            "...W."]
    )
    assert_equals(shortest_path(a[:]), False)
    print("PASSED")
    a = "\n".join(
        [
            "..W",
            ".W.",
            "W.."]
    )
    assert_equals(shortest_path(a[:]), False)
    print("PASSED")
    a = "\n".join(
        [
            ".WWWW",
            ".W...",
            ".W.W.",
            ".W.W.",
            "...W."]
    )
    assert_equals(shortest_path(a[:]), 14)
    print("PASSED")
    a = "\n".join(
        [
            ".W...",
            "W....",
            ".....",
            ".....",
            "....."]
    )
    assert_equals(shortest_path(a[:]), False)
    print("PASSED")
    a = "\n".join(
        [
            ".W",
            "W."]
    )
    assert_equals(shortest_path(a[:]), False)
    print("PASSED")

    describe("\nRandom tests:")

    import heapq
    from random import randint as R, sample as S

    def reference(s):
        s = [list(x) for x in s.split()]
        f = len(s) - 1
        q = [(0, 0, (0, 0))]
        while q:
            _, n, (x, y) = heapq.heappop(q)
            if x == y == f: return n
            n += 1
            for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                X, Y = x + dx, y + dy
                if 0 <= X <= f and 0 <= Y <= f and s[X][Y] == ".":
                    s[X][Y] = "W"
                    heapq.heappush(q, (n + f - X + f - Y, n, (X, Y)))
        return 0

    count = 0
    for i in range(10, 50):
        for _ in range(10):
            total = R(i ** 2 // 5, i ** 2 // 3)
            locations = set(S(range(0, i ** 2 - 2), total))
            field = []
            line = "."
            for j in range(i ** 2 - 2):
                if len(line) < i:
                    line += "W" if j in locations else "."
                else:
                    field.append(line)
                    line = "W" if j in locations else "."
            field.append(line + "{}".format("." if i > 1 else ""))
            field = "\n".join(field)
            assert_equals(shortest_path(field), reference(field))
            count += 1

    print("PASSED ALL {} RANDOM TESTS".format(count))


if __name__ == '__main__':
    print("Best path tests:")
    best_path_tests()

    print("~~~~~~~~~~~~")
    print("~~~~~~~~~~~~")
    print("~~~~~~~~~~~~")
    print("Shortest path tests:")
    shortest_path_tests()
