from itertools import count
from collections import defaultdict

# 60d0fd89efbd700055f491c4
# find minimum number of steps to converge on a node in a graph from multiple starting nodes
# every step we move from each node to one of its neighbors
def converge(g, us):
    us     = set(us)
    cnts   = (defaultdict(int), defaultdict(int))
    floods = [ [[u], ({u},set())] for u in us ]
    tic, N = 0, len(us)
    
    for u in us:
        cnts[tic][u] += 1
        if cnts[tic][u]==N: return 0
    
    for step in count(1):
        tic ^= 1
        for i, (bag,seens) in enumerate(floods):
            if not bag: return None

            tmp = []
            for node in bag:
                for neigh in g[node]:
                    if neigh in seens[tic]: continue
                    seens[tic].add(neigh)
                    cnts[tic][neigh] += 1
                    if cnts[tic][neigh] == N: return step
                    tmp.append(neigh)
            else:
                floods[i][0] = tmp

# #################################
from heapq import heappush, heappop

def converge_v2(g, coins):
    coins = set(coins)
    if len(coins) <= 1: return 0
    # keeps track of which coins has reached each vertex in an even or odd number of steps
    reached = {vertex: {0: 0, 1: 0} for vertex in g}
    heap = []
    p = 1
    for coin in coins:
        reached[coin][0] = p
        heappush(heap, (0, coin))
        p <<= 1
    p -= 1

    while heap:
        step, vertex = heappop(heap)
        parity = step % 2
        reached_coins = reached[vertex][parity]
        for v in g[vertex]:
            if reached[v][1 - parity] | reached_coins != reached[v][1 - parity]:
                reached[v][1 - parity] |= reached_coins
                if reached[v][1 - parity] == p: return step + 1
                heappush(heap, (step + 1, v))
                
# #################################               
from itertools import count, cycle

def converge_v3(g, cn):
    q = {x: 0 for x in g}
    r = {**q}
    h = iter(cycle(((q,1),(r,2))))
    m = {x:[{x},set(),set()] for x in cn}
    ab = list(map(lambda x: [{x}, set(), set()], cn))
    for o in count():
        d, e = next(h)
        for i, x in enumerate(ab):
            a, b, c = x[0], x[e], set()
            if not a: return None
            for v in a - b:
                d[v] += 1
                if d[v] == len(cn): return o
                b.add(v)
                c.update(g[v])
            else: ab[i][0] = c
