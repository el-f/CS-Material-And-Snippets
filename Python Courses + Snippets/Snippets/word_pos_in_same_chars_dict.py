import math
import functools


def dict_pos(word: str):
    l, s, pos = sorted(word), set(word), 1
    for i, c in enumerate(word):
        pos += l.index(c) * math.factorial(len(word) - i - 1) // functools.reduce(
            lambda x, y: x * math.factorial(l.count(y)), s, 1
        )
        l.pop(l.index(c))
    return pos


if __name__ == '__main__':
    cases = {'A': 1, 'ABAB': 2, 'AAAB': 1, 'BAAA': 4, 'QUESTION': 24572, 'BOOKKEEPER': 10743,
             'IMMUNOELECTROPHORETICALLY': 718393983731145698173}
    for word, pos in cases.items():
        if dict_pos(word) != pos:
            print(f'FAILED: {word} should be {pos} but is {dict_pos(word)}')
        else:
            print(f'PASSED: {word} is {pos}')
    print('done')
