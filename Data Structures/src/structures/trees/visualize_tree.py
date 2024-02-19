import matplotlib.pyplot as plt
import networkx as nx
from functools import reduce

# define the tree structure
graph_dict = {
  0: [1, 2],
  1: [3, 8],
  3: [4, 5, 7],
  2: [6],
}

# ------------------------------------------------------------------------------

edges = [
  (parent, child)
  for parent, children in graph_dict.items()
  for child in children
]

# create a directed graph from edges
G = nx.DiGraph(edges)

# verify that the graph is a tree (i.e., it has no cycles)
if not nx.is_tree(nx.DiGraph(graph_dict)):
    raise ValueError("The graph is not a tree")

# define node positions explicitly for the given tree structure
def build_positions(edges):
    pos = {0: (0, 0)}
    children_for_each_parent = reduce(lambda acc, edge: {**acc, edge[0]: 1 + acc.get(edge[0], 0)}, edges, {})
    counted = {}
    
    for parent, child in edges:
        child_num = counted.get(parent, 1); counted[parent] = child_num + 1
        x_extra_offset = child_num if children_for_each_parent[parent] > 2 else 1
        pos[child] = pos[parent][0] + ((-1) ** child_num) * x_extra_offset, pos[parent][1] - 1

    seen = set()
    for p in pos:
        if pos[p] in seen:
            pos[p] = (pos[p][0], pos[p][1] + .5)
        seen.add(pos[p])
    
    return pos

poses = build_positions(edges)

# draw the tree
plt.figure(figsize=(8, 5))
nx.draw(G, poses, with_labels=True, arrows=False, node_size=2000, node_color="skyblue", font_size=16, font_weight="bold", edge_color="red", width=2)
# plt.title("Visualized Tree Structure")
plt.axis("off")  # turn off the axis
plt.show()

