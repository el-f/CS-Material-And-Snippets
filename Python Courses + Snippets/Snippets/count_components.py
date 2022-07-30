from collections import Counter, deque

# 5856f3ecf37aec45e6000091

def components(grid):
    grid = grid.split("\n")
    visited = set()
    ccs = {}
    Q = deque()

    def check(y, x, sid):
        if (y, x) in visited or not (0 <= y < len(grid)) or not (0 <= x <= len(grid[y])) or grid[y][x] != ' ':
            return
        visited.add((y, x))
        if y % 2 and x % 3:
            ccs[sid] += 1
        for dy, dx in ((0, 1), (0, -1), (1, 0), (-1, 0)):
            Q.append((y + dy, x + dx, sid))

    set_id = 0
    for y in range(len(grid)):
        for x in range(len(grid[y])):
            if grid[y][x] == ' ' and (y, x) not in visited:
                ccs[set_id] = 0
                Q.append((y, x, set_id))
                while Q:
                    check(*Q.pop())
                set_id += 1
    

    lengths = Counter(sorted([ccs[s] // 2 for s in ccs], reverse=True))
    return [(l, lengths[l]) for l in lengths]
