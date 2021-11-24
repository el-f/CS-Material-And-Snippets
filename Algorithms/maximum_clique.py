def maximum_clique(adjacency_matrix):
    """
    Maximum clique algorithm by Carraghan and Pardalos
    :param adjacency_matrix: 
    :return: set of largest clique vertices
    """
    if not adjacency_matrix:
        return set()

    graph = {}
    for a, row in enumerate(adjacency_matrix):
        for b, connected in enumerate(row):
            if connected:
                graph.setdefault(a, set()).add(b)
    if not graph: return {0}

    def clique_search(subset, clique):
        nonlocal max_clique
        if not subset:
            max_clique = max((max_clique, clique), key=len)
            return
        while subset:
            if len(subset) + len(clique) <= len(max_clique):
                return
            x = subset.pop()
            clique_search(subset & graph[x], clique | {x})

    max_clique = set()
    clique_search(set(graph), set())
    return max_clique

  
  def maximum_clique_size_ostergard(matrix):
    """
    Patric R.J. Östergård
    A fast algorithm for the maximum clique problem
    https://www.sciencedirect.com/science/article/pii/S0166218X01002906
    :param adjacency_matrix: 
    :return: size of set of largest clique vertices
    """
    n = len(matrix)
    graph = {1 << i: sum(1 << j for j, x in enumerate(r) if x and j != i) for i, r in enumerate(matrix)}
    max_size, c = 0, {1 << i: 0 for i in range(n)}

    def find(vs, size):
        nonlocal max_size
        if not vs:
            if size > max_size:
                max_size = size
                return True
        else:
            m = bin(vs).count('1')
            while vs and size + m > max_size:
                v = vs & -vs
                if size + c[v] <= max_size:
                    return False
                if find(vs & graph[v], size + 1):
                    return True
                vs ^= v
                m -= 1
        return False

    s = 0
    for i in range(n - 1, -1, -1):
        v = 1 << i
        find(graph[v] & s, 1)
        c[v] = max_size
        s |= v
    return max_size
