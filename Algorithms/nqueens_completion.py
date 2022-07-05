def queens(placed_queen, n):
    def is_valid(i, x):
        j, y = qs[i], qs[x]
        return j == y or abs(i - x) == abs(j - y)

    def dfs(col=0):
        if col == qx:      return dfs(col + 1)
        if col == len(qs): return True

        for y in range(n):
            qs[col] = y
            if (not any(is_valid(col, ii) for ii in range(col))
                    and (qx < col or not is_valid(col, qx))
                    and dfs(col + 1)):
                return True

    qx, qy = ord(placed_queen[0]) - 97, (int(placed_queen[1]) or 10) - 1
    qs = [qy if col == qx else 0 for col in range(n)]
    dfs()
    return ','.join(f"{chr(x + 97)}{str(y + 1)[-1]}" for x, y in enumerate(qs))


# ****************************
# ****** Random tests ********
# ****************************

print("Random tests")


def random_tests():
    import random

    def _format_pos(row, col):
        return "abcdefghij"[col] + "1234567890"[row]

    def _parse_pos(pos):
        parsed_col = "abcdefghij".find(pos[0])
        parsed_row = "1234567890".find(pos[1])
        return parsed_row, parsed_col

    def _check_solution_valid(solution, required, size):

        positions = solution.split(",")

        if len(positions) != size:
            print(f"Invalid number of columns: {len(positions)}, expected {size}")
            return False

        if required not in positions:
            print(f"Queen not found in required position {required} in solution {solution}")
            return False

        result = [None] * size

        for pos in positions:
            if len(pos) != 2:
                print(f"{pos} is not a valid position")
                return False

            (row, col) = _parse_pos(pos)
            if not (0 <= col < size and 0 <= row < size):
                print(f"{pos} is not a valid position for a board of size {size}")
                return False

            if result[row] is not None:
                print(f"Queen at {pos} can be attacked by queen at " + _format_pos(row, result[row]))
                return False

            result[row] = col

        cols = [None] * size
        ldiag = [None] * 2 * size
        rdiag = [None] * 2 * size
        noatk = (-1, -1)
        for row in range(size):
            col = result[row]
            pos = _format_pos(row, col)

            if col is None:
                print(f"No queen in row {row + 1}")
                return False

            if col < 0 or col >= size:
                print(f"Queen at {pos} is outside bounds")
                return False

            atk = cols[col] or ldiag[col + row] or rdiag[col - row + size - 1] or noatk

            if atk is not noatk:
                print(f"Queen at {pos} can be attacked by queen at " + _format_pos(atk[0], atk[1]))
                return False

            cols[col] = ldiag[col + row] = rdiag[col - row + size - 1] = (row, col)

        # print("Solution " + solution + " is valid")
        return True

    def select(testCases, size):
        random.shuffle(testCases)
        return testCases[:size * 2]

    sizes = [1, 4, 5, 6, 7, 8, 9, 10]
    toTest = []
    for size in sizes:
        testCases = []
        if size == 1:
            testCases = ["a1"]
        elif size == 4:
            testCases = "a2 a3 b1 b4 c1 c4 d2 d3".split(" ")
        elif size == 6:
            testCases = "a2 a3 a4 a5 b1 b3 b4 b6 c1 c2 c5 c6 d1 d2 d5 d6 e1 e3 e4 e6 f2 f3 f4 f5".split(" ")
        else:
            for row in range(size):
                for col in range(size):
                    testCases.append(_format_pos(row, col))
        testCases = select(testCases, size)
        for testCase in testCases:
            toTest.append((testCase, size));

    def check(pos, size):
        actual = queens(pos, size)
        if _check_solution_valid(actual, pos, size):
            print("PASSED")
        else:
            print(f"FAILED: Solution {actual} is not valid for size={size}, pos={pos}")

    for (pos, size) in toTest:
        print(f"Size {size}, mandatory position: {pos}", end="\t")
        check(pos, size)


if __name__ == '__main__':
    random_tests()
