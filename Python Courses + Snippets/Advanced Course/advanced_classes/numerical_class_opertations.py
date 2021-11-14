class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return "<Point x:{0}, y:{1}>".format(self.x, self.y)

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)

    # def __iadd__(self, other): #unnecessary
    #     self.x += other.x
    #     self.y += other.y
    #     return self


def main():
    p1 = Point(10, 20)
    p2 = Point(30, 30)
    print(p1, p2)

    p3 = p1 + p2
    print(p3)

    p4 = p2 - p1
    print(p4)

    p1 += p2
    print(p1)


if __name__ == '__main__':
    main()
