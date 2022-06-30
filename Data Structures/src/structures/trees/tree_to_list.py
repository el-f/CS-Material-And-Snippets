class Node:
    def __init__(self, data, child_nodes=None):
        self.data = data
        self.child_nodes = child_nodes


def tree_to_list(tree_root):
    l = []
    q = [tree_root]

    def adj(n):
        if not n: return
        if n.child_nodes: [q.append(c) for c in n.child_nodes]

    while q:
        c = q.pop(0)
        l.append(c.data)
        adj(c)
    return l
