import matplotlib.pyplot as plt
import networkx as nx

# define the tree structure
graph_dict = {
  0: [1, 2],
  1: [3],
  3: [4, 5],
  2: [6]
}

# ------------------------------------------------------------------------------

edges = [
  (parent, child)
  for parent, children in graph_dict.items()
  for child in children
]

# create a directed graph from edges
G = nx.DiGraph(edges)

# define node positions explicitly for the given tree structure
def build_positions(edges):
    pos = {}
    pos[0] = (0, 0)
    children_for_each_parent = {}
    for edge in edges:
        parent, child = edge
        child_num = children_for_each_parent.get(parent, 1)
        children_for_each_parent[parent] = child_num + 1
        pos[child] = pos[parent][0] + (-1) ** child_num, pos[parent][1] - 1
    return pos

poses = build_positions(edges)

# draw the tree
plt.figure(figsize=(8, 5))
nx.draw(G, poses, with_labels=True, arrows=False, node_size=2000, node_color="skyblue", font_size=16, font_weight="bold")
plt.title("Visualized Tree Structure")
plt.axis("off")  # turn off the axis
plt.show()
