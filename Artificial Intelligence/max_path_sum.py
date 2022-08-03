def mps(pyramid: list) -> int:
    for row in range(len(pyramid) - 2, -1, -1):
        pyramid[row] = [
            max(
                pyramid[row][col] + pyramid[row + 1][col],
                pyramid[row][col] + pyramid[row + 1][col + 1]
            ) for col in range(len(pyramid[row]))
        ]
    return pyramid[0][0]

