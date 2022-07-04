from itertools import combinations
from random import randrange, sample


#  590a924c7dfc1a238d000047
def smallest_team_with_all_skills(n, candidates):
    for i in range(1, len(candidates) + 1):
        combs = combinations(candidates, i)
        if any(len(set(sum(comb, []))) == n for comb in combs):
            return i + 1

    return -1


def fixed_tests():
    test_cases = [
        ((3, [[0, 2], [1, 2], [0, 1], [0]]), 3),
        ((6, [[0, 1], [1, 3], [0, 2], [0, 5], [1, 4]]), 5),
        ((1, [[], []]), -1),
        ((1, []), -1,),
        ((2, [[], [0, 1]]), 2),
        ((1, [[0], [0]]), 2),
        ((2, [[0], [0]]), -1),
        ((8, [[0, 1], [1, 3], [0, 2], [0, 5], [1, 4], [6, 7], [6, 0]]), 6),
    ]

    for (n, candidates), expected in test_cases:
        assert smallest_team_with_all_skills(n, candidates) == expected


def random_tests():
    def reference(_n, _candidates):
        return solve(set(range(_n)), [*map(set, _candidates)], 1) or -1

    def solve(categories, _candidates, _n):
        if not categories:
            return _n
        if _candidates:
            return min(filter(None, (
                solve(categories, _candidates[1:], _n), solve(categories - _candidates[0], _candidates[1:], _n + 1))),
                       default=None)

    def random_test_case():
        _n = randrange(1, 11)
        _candidates = [sorted(sample(range(_n), randrange(_n))) for _ in range(randrange(11))]
        return (_n, _candidates), reference(_n, _candidates)

    test_cases = [random_test_case() for _ in range(500)]

    for (n, candidates), expected in test_cases:
        assert smallest_team_with_all_skills(n, candidates) == expected


if __name__ == '__main__':
    fixed_tests()
    random_tests()
