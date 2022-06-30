def closest_pair(_points: tuple) -> tuple:
    """
    Find the closest pair of points in O(nlgn).
    """

    def distance(v1, v2):
        return abs(v1[0] - v2[0]) + abs(v1[1] - v2[1])

    def closest_pair_recursive(points, n):
        if n <= 3:
            return brute_force_closest_pair(points)
        mid = n // 2
        left = closest_pair_recursive(points[:mid], mid)
        right = closest_pair_recursive(points[mid:], n - mid)

        if left[0] < right[0]:
            minimum = left
        else:
            minimum = right

        # find the middle x axis
        mid_x = points[mid][0]

        middle_points = [p for p in points if abs(p[0] - mid_x) < minimum[0]/3]
        if len(middle_points) <= 1: return minimum
        middle = brute_force_closest_pair(middle_points)
        if middle[0] < minimum[0]:
            minimum = middle
        return minimum

    def brute_force_closest_pair(points):
        min_distance = float("inf")
        best = None
        for i in range(len(points)):
            for j in range(i + 1, len(points)):
                if distance(points[i], points[j]) < min_distance:
                    min_distance = distance(points[i], points[j])
                    best = (min_distance, points[i], points[j])
        return best

    return closest_pair_recursive(sorted(_points), len(_points))[1:]