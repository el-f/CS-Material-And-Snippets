import math


# solution for this kata: 540afbe2dc9f615d5e000425

class Sudoku(object):
    def __init__(self, data):
        self.mat = data

    def is_valid(self):
        if not all(len(row) == len(self.mat) for row in self.mat):
            return False
        if len(self.mat) == 1 and self.mat[0][0] != 1 or type(self.mat[0][0]) == int:
            return False

        size = len(self.mat)
        root = math.sqrt(size)
        if int(root) != root:
            return False

        for i in range(size):
            for j in range(size):
                for i2 in range(size):
                    for j2 in range(size):
                        if self.mat[i][j] == 0:
                            return False
                        if i == i2 and j == j2:
                            continue
                        if self.mat[i][j] == self.mat[i2][j2]:
                            if i == i2 or j == j2 or (i // root == i2 // root and j // root == j2 // root):
                                return False

        return True
