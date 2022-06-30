import numpy as np
import heapq as hq


# each cell is a node, and each edge is a weight made up of the difference between the two cells
def path_finder_weighted(maze):
    maze = maze.split("\n")
    n = len(maze)
    visited = np.ones((n, n)) * np.inf
    heap = [(0, 0, 0)]
    while heap:
        dist, x, y = hq.heappop(heap)
        if x == n - 1 and y == n - 1:
            return dist
        for i, j in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if 0 <= i < n and 0 <= j < n and \
                    (new_dist := dist + abs(int(maze[x][y]) - int(maze[i][j]))) < visited[i][j]:
                visited[i][j] = new_dist
                hq.heappush(heap, (new_dist, i, j))


# each cell is a node, and each edge is a weight of 1
def path_finder(maze):
    maze = maze.split("\n")
    n = len(maze)
    visited = np.zeros((n, n))
    visited[0][0] = 1
    queue = [(0, 0, 0)]
    while queue:
        dist, x, y = hq.heappop(queue)
        if x == n - 1 and y == n - 1:
            return dist
        for i, j in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if 0 <= i < n and 0 <= j < n and maze[i][j] == '.' and visited[i][j] == 0:
                visited[i][j] = 1
                hq.heappush(queue, (dist + 1, i, j))
    return False


# each cell is a node, and each edge is a weight of 0
def is_there_a_path(maze):
    maze = maze.split("\n")
    w, h = len(maze[0]) - 1, len(maze) - 1
    Q = [(0, 0)]
    seen = set()

    def get_adj(r, c):
        for i, j in ((0, 1), (1, 0), (0, -1), (-1, 0)):
            if (0 <= r + i <= h) and (0 <= c + j <= w) and \
                    maze[r + i][c + j] != 'W' and (r + i, c + j) not in seen:
                Q.append((r + i, c + j))
                seen.add((r + i, c + j))

    while len(Q) > 0:
        y, x = Q.pop(0)
        if (y, x) == (h, w):
            return True
        get_adj(y, x)

    return False
