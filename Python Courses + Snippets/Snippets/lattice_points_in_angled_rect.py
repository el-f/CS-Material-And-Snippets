# 5886e082a836a691340000c3
# A rectangle with sides equal to even integers a and b is drawn on the Cartesian plane. Its center (the intersection point of its diagonals) coincides with the point (0, 0), but the sides of the rectangle are not parallel to the axes; instead, they are forming 45 degree angles with the axes.
# How many points with integer coordinates are located inside the given rectangle (including on its sides)?

def rectangle_rotation(a, b):
    x = a / 2 ** .5 / 2
    y = b / 2 ** .5 / 2
    r1 = [x//1 * 2 + 1, y//1 * 2 + 1]
    r2 = [r1[0] + (-1 if x % 1 < .5 else 1), r1[1] + (-1 if y % 1 < .5 else 1)]
    return r1[0] * r1[1] + r2[0] * r2[1]


def rectangle_rotation_v2(a, b):
    a //= 2**0.5
    b //= 2**0.5
    r = (a + 1) * (b + 1) + a * b

    return r + r % 2 - 1
