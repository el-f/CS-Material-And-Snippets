def same_group(p, q):
    x1, y1 = p
    x2, y2 = q
    return x1 == x2 or y1 == y2 or (x1 // 3 == x2 // 3 and y1 // 3 == y2 // 3)

def to_pairs(xss):
    return [ ((x, y), set(range(1, 10)) if xss[y][x] == 0 else { xss[y][x] }) for x in range(0, 9) for y in range(0, 9) ]

def from_pairs(pairs):
    result = [ [ None for _ in range(9) ] for _ in range(9) ]
    for pos, value in pairs:
        x, y = pos
        result[y][x] = value
    return result

def solve(fixed, todo):
    if todo:
        position, domain = min(todo, key=lambda pair: len(pair[1]))
        for x in domain:
            new_todo = [ (p, d - {x} if same_group(position, p) else d) for p, d in todo if p != position ]
            yield from solve( [*fixed, (position, x)], new_todo )
    else:
        yield fixed

def sudoku_solver(puzzle):
    if len(puzzle) != 9 or any(len(row) != 9 for row in puzzle) or any(any(c not in range(0, 10) for c in row) for row in puzzle):
        raise RuntimeError('Invalid input')

    pairs = to_pairs(puzzle)
    solutions = solve([], pairs)
    sol1 = next(solutions)
    try:
        next(solutions)
        multiple_solutions = True
    except:
        multiple_solutions = False

    if multiple_solutions:
        raise RuntimeError('Multiple solutions')
    else:
        return from_pairs(sol1)