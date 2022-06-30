from collections import Counter
from heapq import heappush, heappop
import re


def frequencies(s):
    return list(Counter(s).items())


def table(freqs):
    trees = sorted((k, c, {c: ''}) for c, k in freqs)
    while trees[1:]:
        k0, c0, t0 = heappop(trees)
        k1, _, t1 = heappop(trees)
        heappush(trees, (k0 + k1, c0, {c: b + s for b, t in (('0', t0), ('1', t1)) for c, s in t.items()}))
    return trees[0][2]


def encode(freqs, s):
    if freqs[1:]:
        return ''.join(map(table(freqs).get, s))


def decode(freqs, bits):
    if freqs[1:]:
        t = {s: c for c, s in table(freqs).items()}
        return re.sub('|'.join(t), lambda m: t[m.group()], bits)
