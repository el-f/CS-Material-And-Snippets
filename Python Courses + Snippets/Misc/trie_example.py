from itertools import product
with open('./words.txt') as f:
    WORDS = f.read().split()

DIRS = set(product(range(-1, 2), repeat=2)) - {(0, 0)}


class Trie:

    def __init__(self):
        self.root = {}

    def insert(self, word):
        cur = self.root
        for char in word:
            if char not in cur:
                cur[char] = {}
            cur = cur[char]
        cur['#'] = ''


trie = Trie()
for word in WORDS:
    trie.insert(word)


def search_for_words_in_grid(puzzle):
    def dfs(x, y, snake, t):
        if len(snake) > 3 and '#' in t:
            res.add(snake)
        for dx, dy in DIRS:
            i, j = x + dx, y + dy
            if N > i >= 0 <= j < M and grid[i][j] != ' ' and not seen[i][j]:
                seen[i][j] = 1
                char = grid[i][j]
                if char in t:
                    dfs(i, j, snake + char, t[char])
                seen[i][j] = 0

    res = set()
    grid = puzzle.split('-')
    N, M = len(grid), len(grid[0])
    for i, j in product(range(N), range(M)):
        char = grid[i][j]
        if char != ' ':
            seen = [[0] * M for _ in range(N)]
            seen[i][j] = 1
            if char in trie.root:
                dfs(i, j, char, trie.root[char])

    return sorted(res, key=lambda w: (len(w), w))


print(
    search_for_words_in_grid('qgru-ntbo-oiel-tohs') == [
        'bite', 'hint', 'into', 'nite', 'note', 'robe', 'role',
        'shin', 'shoe', 'shot', 'ties', 'toes', 'toon', 'tote',
        'being', 'bites', 'intro', 'nitro', 'notes', 'orbit',
        'robin', 'roles', 'shoot', 'burton', 'trouble', 'shooting',
        'troubles', 'troubleshooting'
    ]
)
