# ********************************************
# ******          Version 1             ******
# ********************************************


from collections import deque


def bi_directional_search(graph, start, goal):
    # Check if start and goal are equal.
    if start == goal:
        return [start]
    # Get dictionary of currently active vertices with their corresponding paths.
    active_vertices_path_dict = {start: [start], goal: [goal]}
    # Vertices we have already examined.
    inactive_vertices = set()

    while len(active_vertices_path_dict) > 0:

        # Make a copy of active vertices so we can modify the original dictionary as we go.
        active_vertices = list(active_vertices_path_dict.keys())
        for vertex in active_vertices:
            # Get the path to where we are.
            current_path = active_vertices_path_dict[vertex]
            # Record whether we started at start or goal.
            origin = current_path[0]
            # Check for new neighbours.
            current_neighbours = set(graph[vertex]) - inactive_vertices
            # Check if our neighbours hit an active vertex
            if len(current_neighbours.intersection(active_vertices)) > 0:
                for meeting_vertex in current_neighbours.intersection(active_vertices):
                    # Check the two paths didn't start at same place. If not, then we've got a path from start to goal.
                    if origin != active_vertices_path_dict[meeting_vertex][0]:
                        # Reverse one of the paths.
                        active_vertices_path_dict[meeting_vertex].reverse()
                        # return the combined results
                        return active_vertices_path_dict[vertex] + active_vertices_path_dict[meeting_vertex]

            # No hits, so check for new neighbours to extend our paths.
            if len(set(current_neighbours) - inactive_vertices - set(active_vertices)) == 0:
                # If none, then remove the current path and record the endpoint as inactive.
                active_vertices_path_dict.pop(vertex, None)
                inactive_vertices.add(vertex)
            else:
                # Otherwise extend the paths, remove the previous one and update the inactive vertices.
                for neighbour_vertex in current_neighbours - inactive_vertices - set(active_vertices):
                    active_vertices_path_dict[neighbour_vertex] = current_path + [
                        neighbour_vertex]
                    active_vertices.append(neighbour_vertex)
                active_vertices_path_dict.pop(vertex, None)
                inactive_vertices.add(vertex)

    return None


# ********************************************
# ******          Version 2             ******
# ********************************************

class Node:
    def __init__(self, val, neighbors=[]):
        self.val = val
        self.neighbors = neighbors
        # whether the node was reached by the BFS that started from source
        self.visited_right = False
        # whether the node was reached by the BFS that started from destination
        self.visited_left = False
        # used for retrieving the final path from source to the meeting point
        self.parent_right = None
        # used for retrieving the final path from the meeting point to destination
        self.parent_left = None


# class Queue:
#    pass  # implement it yourself


def bidirectional_search(s, t):
    def extract_path(node):
        """return the path when both BFS's have met"""
        node_copy = node
        path = []

        while node:
            path.append(node.val)
            node = node.parent_right

        path.reverse()
        del path[-1]  # because the meeting node appears twice

        while node_copy:
            path.append(node_copy.val)
            node_copy = node_copy.parent_left
        return path

    q = deque([])
    q.append(s)
    q.append(t)
    s.visited_right = True
    t.visited_left = True

    while len(q) > 0:
        n = q.pop()

        if n.visited_left and n.visited_right:  # if the node visited by both BFS's
            return extract_path(n)

        for node in n.neighbors:
            if n.visited_left == True and not node.visited_left:
                node.parent_left = n
                node.visited_left = True
                q.append(node)
            if n.visited_right == True and not node.visited_right:
                node.parent_right = n
                node.visited_right = True
                q.append(node)

    # not found
    return False


def test_ver2():
    n0 = Node(0)
    n1 = Node(1)
    n2 = Node(2)
    n3 = Node(3)
    n4 = Node(4)
    n5 = Node(5)
    n6 = Node(6)
    n7 = Node(7)
    n0.neighbors = [n1, n5]
    n1.neighbors = [n0, n2, n6]
    n2.neighbors = [n1]
    n3.neighbors = [n4, n6]
    n4.neighbors = [n3]
    n5.neighbors = [n0, n6]
    n6.neighbors = [n1, n3, n5, n7]
    n7.neighbors = [n6]
    print(bidirectional_search(n0, n4))
