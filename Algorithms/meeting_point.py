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