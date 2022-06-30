def is_bipartite(db: dict) -> bool:
    db = dict(db)
    stk = list(db)
    v = [0] * len(db)

    while stk:
        a = stk.pop()
        if a not in db: continue

        lst = db.pop(a)
        v[a] = v[a] or 1
        opp = v[a] ^ 3
        for b in lst:
            if v[b] and v[b] != opp: return False
            v[b] = opp

        stk.extend(lst)
    return True


if __name__ == '__main__':
    connected_tests = [({0: [1, 2], 1: [0], 2: [0], 3: []}, True),
                       ({0: [1, 2], 1: [0, 3], 2: [0, 3], 3: [1, 2]}, True),
                       ({0: [1, 2, 3], 1: [0], 2: [0, 3], 3: [0, 2]}, False),
                       ({0: [1, 2], 1: [0], 2: [0, 3], 3: [2, 4, 5],
                         4: [3], 5: [3]}, True),
                       ({0: [1, 2], 1: [0], 2: [0, 3], 3: [2, 4, 5],
                         4: [3, 5], 5: [3, 4]}, False),
                       ({0: [1, 2, 3, 4], 1: [0, 2, 3, 4],
                         2: [0, 1, 3, 4], 3: [0, 1, 2, 4],
                         4: [0, 1, 2, 3]}, False),
                       ({0: [3], 1: [2], 2: [1, 3],
                         3: [2, 0, 4], 4: [3]}, True),
                       ({0: [6, 5], 1: [6], 2: [7, 8, 4],
                         3: [8, 4], 4: [3, 2], 5: [9, 8, 7, 0],
                         6: [0, 1, 7], 7: [2, 5, 6], 8: [2, 3, 5],
                         9: [5]}, True),
                       ({0: [4], 1: [2], 2: [4, 1, 3],
                         3: [2], 4: [0, 2]}, True)]

    disconnected_tests = [({0: [], 1: [], 2: [], 3: [], 4: []}, True),
                          ({0: [1, 2, 3], 1: [0, 4], 2: [0],
                            3: [0, 5], 4: [1], 5: [3], 6: [7, 8],
                            7: [6], 8: [6, 9, 10], 9: [8], 10: [8, 11],
                            11: [10]}, True),
                          ({0: [1, 2, 3], 1: [0, 4], 2: [0], 3: [0, 5],
                            4: [1], 5: [3], 6: [7, 8], 7: [6],
                            8: [6, 9, 10, 11], 9: [8, 11], 10: [8, 11],
                            11: [8, 9, 10]}, False)]
    for test in connected_tests:
        if is_bipartite(test[0]) != test[1]:
            print('Test failed:', test)
        else:
            print('OK')
    for test in disconnected_tests:
        if is_bipartite(test[0]) != test[1]:
            print('Test failed:', test)
        else:
            print('OK')