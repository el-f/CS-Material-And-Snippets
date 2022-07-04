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


dirs = {(1, 0): "up", (-1, 0): "down", (0, 1): "left", (0, -1): "right"}  # reversed for path reconstruction optimization.


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
