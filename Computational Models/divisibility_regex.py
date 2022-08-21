# 5993c1d917bc97d05d000068

def dfa(n):
    return {r: {(r*2) % n: '0', (r*2+1) % n: '1'} for r in range(n)}


def dfa2regex(d):
    m = len(d) - 1
    if m == 0:
        return '^(%s)+$' % d[0][0]

    def sub(s, e):
        sme = d[s][m] + ('(?:%s)*' % d[m][m] if m in d[m] else '') + d[m][e]
        return '(?:%s|%s)' % (d[s][e], sme) if e in d[s] else sme

    def link(s, e):
        return sub(s, e) if m in d[s] and e in d[m] else d[s][e]

    def ends(s):
        return set(d[s]) | (set(d[m]) if m in d[s] else set())

    def node(s):
        return {e: link(s, e) for e in ends(s) if e != m}
    return dfa2regex({s: node(s) for s in d if s != m})


def regex_divisible_by(n):
    return dfa2regex(dfa(n)) if n > 1 else '^[10]+$'

# ##############################
from itertools import product


def regex_divisible_by_v2(n):
    if n == 1:
        return r"^(?:0|1)+$"
    edges = dict()
    for i, j in product(range(n), range(2)):
        edges[(i, (i*2+j) % n)] = str(j)
    for i in range(n - 1, 0, -1):
        self_loop = f"(?:{edges[(i, i)]})*" if (i, i) in edges else ""
        for j, k in product(range(i), repeat=2):
            if (j, i) in edges and (i, k) in edges:
                edge = f"{edges[(j, i)]}{self_loop}{edges[(i, k)]}"
                if (j, k) in edges:
                    edges[(j, k)] = f"(?:{edges[(j, k)]}|{edge})"
                else:
                    edges[(j, k)] = edge
    return f"^(?:{edges[(0, 0)]})+$"

# ##############################

def star(x):
    return "(?:"+x+")*" if x else ""


def union(x, y):
    return "(?:"+x+"|"+y+")" if x and y else x or y


def concat(x, y):
    if x is None or y is None:
        return None
    return x+y if x and y else x or y


def regex_divisible_by_v3(N):
    if N == 1:
        # Make specification of NFA cleaner by hard-coding N=1 case
        return "^[01]+$"

    m = N + 1

    # Construct an NFA that accepts a binary string one digit at a time,
    # then convert it to a regex using Brzozowski's algorithm.

    # Specify N+1 states, corresponding to the initial state
    # and "string up to this point = k mod N" for k=1,2,...,N
    # Note that initial state is 0, and the "0 mod N" case is actually state N.
    B = ["" if i == N else None for i in range(m)]

    # Specify transitions from each state corresponding to an extra digit.
    # Note that value k becomes (k*2+0) or (k*2+1) when 0 or 1 is appended.
    A = [[None for _ in range(N+1)] for _ in range(m)]
    for i in range(m):
        A[i][(2*i+0) % N or N] = "0"
        A[i][(2*i+1) % N or N] = "1"

    for n in range(N, -1, -1):
        B[n] = concat(star(A[n][n]), B[n])
        for j in range(n):
            A[n][j] = concat(star(A[n][n]), A[n][j])
        for i in range(n):
            B[i] = union(B[i], concat(A[i][n], B[n]))
            for j in range(n):
                A[i][j] = union(A[i][j], concat(A[i][n], A[n][j]))
        for i in range(n):
            A[i][n] = None

    return "^" + B[0] + "$"
