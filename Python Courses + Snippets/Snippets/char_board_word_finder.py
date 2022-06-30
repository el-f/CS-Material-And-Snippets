def find_word(board, word):
    def search_from(start):
        seen = set()
        Q = [start]

        def adj(r, c, pos):
            for i, j in ((0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)):
                if (0 <= r + i < len(board)) and (0 <= c + j < len(board[0])) and \
                        board[r + i][c + j] == word[pos] and (r + i, c + j) not in seen:
                    Q.append((r + i, c + j, pos))

        while Q:
            _r, _c, _pos = Q.pop(0)
            if _pos == len(word) - 1: return True
            adj(_r, _c, _pos + 1)
            seen.add((_r, _c))

    for ri, row in enumerate(board):
        if any(search_from((ri, ci, 0)) for ci, ch in enumerate(row) if board[ri][ci] == word[0]): return True
    return False
