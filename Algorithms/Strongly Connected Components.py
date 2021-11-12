# Kosaraju's algorithm to find strongly connected components in Python
from collections import defaultdict
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import connected_components
from itertools import groupby


# version as a function: input - adj list | output - SCC sets
def find_scc(graph):
    visited = [False] * len(graph)
    stack = []
    sccs = []

    def dfs(curr_node, first_run):
        if visited[curr_node]:
            return

        visited[curr_node] = True

        for adj in graph[curr_node]:
            if not visited[adj]:
                dfs(adj, first_run)

        if first_run:
            stack.append(curr_node)
        else:
            sccs[-1].add(curr_node)

    def transpose():
        t = [set() for _ in range(len(graph))]
        for nd in range(len(graph)):
            for adj in graph[nd]:
                t[adj].add(nd)
        return t

    for node in range(len(graph)):
        dfs(node, True)

    graph = transpose()
    visited = [False] * len(graph)

    while stack:
        node = stack.pop()
        if not visited[node]:
            sccs.append(set())
            dfs(node, False)

    return sccs


# version using scipy
def strongly_connected_components(graph):
    if not graph:
        return graph
    # Compressed Sparse Row matrix
    csr_mat = [[0 for _ in range(len(graph))] for __ in range(len(graph))]
    for j, i in enumerate(graph):
        for p in i:
            csr_mat[j][p] = 1

    a, b = connected_components(
        csgraph=csr_matrix(csr_mat),
        directed=True,
        connection='strong',
        return_labels=True
    )

    return [set(map(lambda x: x[0], j)) for i, j in
            groupby(sorted(enumerate(b), key=lambda x: x[1]), key=lambda x: x[1])]


# Version allowing building the graph then applying the algorithm and *printing* the results
class Graph:

    def __init__(self, vertex):
        self.V = vertex
        self.graph = defaultdict(list)

    # Add edge into the graph
    def add_edge(self, s, d):
        self.graph[s].append(d)

    # dfs
    def dfs(self, d, visited_vertex):
        visited_vertex[d] = True
        print(d, end=' ')
        for i in self.graph[d]:
            if not visited_vertex[i]:
                self.dfs(i, visited_vertex)

    def fill_order(self, d, visited_vertex, stack):
        visited_vertex[d] = True
        for i in self.graph[d]:
            if not visited_vertex[i]:
                self.fill_order(i, visited_vertex, stack)
        stack.append(d)

    # transpose the matrix
    def transpose(self):
        transposed_graph = Graph(self.V)

        for i in self.graph:
            for j in self.graph[i]:
                transposed_graph.add_edge(j, i)
        return transposed_graph

    # Print strongly connected components
    def print_scc(self):
        stack = []
        visited_vertex = [False] * self.V

        for i in range(self.V):
            if not visited_vertex[i]:
                self.fill_order(i, visited_vertex, stack)

        gr = self.transpose()

        visited_vertex = [False] * self.V

        while stack:
            i = stack.pop()
            if not visited_vertex[i]:
                gr.dfs(i, visited_vertex)
                print()


# Tests
def fixed_tests(scc_func):
    message = "Calculated components do not match: {} should equal {}"

    def fixed_test(_graph, expected):
        actual = scc_func(_graph)
        if len(expected) != len(actual):
            print(message.format(actual, expected))
            return
        for scc in actual:
            if scc not in expected:
                print(message.format(actual, expected))
                return

    graph = [[1], [2, 3, 4], [0, 3], [5], [5, 6], [3], [4, 7], [5, 6]]
    expect = [{3, 5}, {4, 6, 7}, {0, 1, 2}]
    fixed_test(graph, expect)

    graph = [[1], [2], [3, 4], [0], [5], [6], [4, 7], []]
    expect = [{7}, {4, 5, 6}, {0, 1, 2, 3}]
    fixed_test(graph, expect)

    graph = [[5, 1], [6, 0, 2], [3, 7], [5, 1], [1], [3], [9], [], [6], [3]]
    expect = [{7}, {0, 1, 2, 3, 5, 6, 9}, {4}, {8}]
    fixed_test(graph, expect)

    fixed_test([], [])

    fixed_test([[]], [{0}])

    graph = [[1], [2], [3], [4], [5], [0]]
    expect = [{0, 1, 2, 3, 4, 5}]
    fixed_test(graph, expect)


def manual_version_test():
    g = Graph(8)
    g.add_edge(0, 1)
    g.add_edge(1, 2)
    g.add_edge(2, 3)
    g.add_edge(2, 4)
    g.add_edge(3, 0)
    g.add_edge(4, 5)
    g.add_edge(5, 6)
    g.add_edge(6, 4)
    g.add_edge(6, 7)

    print("Strongly Connected Components:")
    g.print_scc()


if __name__ == '__main__':
    fixed_tests(strongly_connected_components)
    fixed_tests(find_scc)
    manual_version_test()
