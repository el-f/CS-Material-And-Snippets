from math import dist


# nodes are y, x tuples so the distance between them is the euclidean distance
def MST(nodes):
    min_weight = {node: float('inf') for node in nodes}
    total_dist = 0
    current = nodes.pop()
    while nodes:
        for node in nodes:
            dist_to_current = dist(node, current)
            if dist_to_current < min_weight[node]:
                min_weight[node] = dist_to_current
        current, shortest_dist = min(min_weight.items(), key=lambda x: x[1])
        total_dist += shortest_dist
        del min_weight[current]
        nodes.remove(current)
    return total_dist
