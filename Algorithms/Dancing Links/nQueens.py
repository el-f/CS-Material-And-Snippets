from itertools import *
import numpy as np


def trace(msg):
    traceEnabled = True
    if traceEnabled:
        print(msg)


def nQueen(n):
    board = np.zeros((n, n)).astype(int)
    problem = NQueens(board)
    solution = problem.solve()
    print(solution)
    answer = []
    for x in range(n):
        for y in range(n):
            num = board[y][x]
            if num > 0:
                answer.append(y)
    return answer


# ********************************************
#                  N-QUEENS
# ********************************************


class NQueens:
    def __init__(self, board):
        self.board = board
        self.size = len(board)

    def solve(self):
        grid = list(self.board)
        tree = self.buildTree()
        dlx = DLX(tree)
        solution = dlx.solveAny()
        if len(solution) > 0:
            self.applySolution(grid, solution[0])
        return grid

    def applySolution(self, grid, solution):
        for variable in solution:
            col = int(variable / self.size)
            row = variable % self.size
            grid[row][col] = 1

    def buildTree(self):
        # 5x5: 24 constraints
        #     5 x column
        #     5 x row
        #     5 x diagonal des (secondary)
        #     5 x diagonal asc (secondary)
        offset = 2 * self.size
        primary = list(range(0, offset))
        secondary = list(range(offset, offset + 2 * max(0, 2 * self.size - 3)))
        clues = self.buildClues()
        # 5x5: 25 variables
        #     5 columns, each 5 rows
        variables = list(range(0, self.size * self.size))
        candidates = self.buildCandidates(variables)
        # build the tree
        tree = Tree(primary, secondary, candidates)
        for clue in clues:
            tree.removeClue(clue)
        return tree

    def buildCandidates(self, variables):
        candidates = {}
        for variable in variables:
            col = int(variable / self.size)
            row = variable % self.size
            c_col = col
            c_row = self.size + row
            c_dia_des = row + col + (2 * self.size - 1)
            c_dia_asc = (self.size - 1 - col + row) + (4 * self.size - 4)
            candidates[variable] = [c_col, c_row]
            if 2 * self.size <= c_dia_des < 4 * self.size - 3:
                candidates[variable].append(c_dia_des)
            if 4 * self.size - 3 <= c_dia_asc < 6 * self.size - 6:
                candidates[variable].append(c_dia_asc)
        return candidates

    def buildClues(self):
        clues = []
        for x in range(self.size):
            for y in range(self.size):
                num = self.board[y][x]
                if num > 0:
                    variable = y * self.size + x
                    clues.append(variable)
        return clues


# ********************************************
#                     DLX
# ********************************************


class DLX():
    KEY_BAILOUT = 'bailout'
    KIND_ANY = 0
    KIND_UNIQUE = 1
    KIND_ALL = 2

    def __init__(self, tree, maxdepth=1000):
        self.tree = tree
        self.maxdepth = maxdepth

    def solveAny(self):
        return self.explore(self.KIND_ANY)

    def solveUnique(self):
        return self.explore(self.KIND_UNIQUE)

    def solveAll(self):
        return self.explore(self.KIND_ALL)

    def explore(self, kind):
        solutions = []
        partial = []
        context = {self.KEY_BAILOUT: False}
        depth = 0
        self.dfs(kind, solutions, partial, context, depth)
        return solutions

    def dfs(self, kind, solutions, partial, context, depth):
        if context[self.KEY_BAILOUT] or depth > self.maxdepth:
            return
        if self.tree.head.right == self.tree.head:
            solution = None
            if kind == self.KIND_ANY:
                context[self.KEY_BAILOUT] = True
                solution = list(partial)
            elif kind == self.KIND_UNIQUE:
                if len(solutions) > 0:
                    raise Exception(
                        "There are multiple solutions to the problem"
                    )
                solution = list(partial)
            else:
                solution = list(partial)
            if solution is not None:
                solutions.append(solution)
            return
        column = self.tree.head.right
        for i in takewhile(
                lambda n: n != self.tree.head,
                (n for n in self.tree.head.nextRight())
        ):
            if i.column.size < column.size:
                column = i.column
        column.cover()
        for i in takewhile(
                lambda n: n != column,
                (n for n in column.nextDown())
        ):
            if context[self.KEY_BAILOUT]:
                break
            partial.append(i.row.variable)
            for j in takewhile(
                    lambda n: n != i,
                    (n for n in i.nextRight())
            ):
                j.column.cover()
            self.dfs(kind, solutions, partial, context, depth + 1)
            for j in takewhile(
                    lambda n: n != i,
                    (n for n in i.nextLeft())
            ):
                j.column.uncover()
            partial.pop()
        column.uncover()


class Tree:

    def __init__(self, primary, secondary, candidates):
        self.primay = primary
        self.secondary = secondary
        self.candidates = candidates
        self.columns = {}
        self.rows = {}
        self.head = Node(None, None)
        for constraint in primary:
            column = Node(constraint, None)
            self.columns[constraint] = column
            self.head.pushLeft(column)
        for constraint in secondary:
            column = Node(constraint, None)
            self.columns[constraint] = column
            column.head = self.head
        for variable in candidates:
            row = Node(None, variable)
            self.rows[variable] = row
            self.head.pushUp(row)
            for constraint in candidates[variable]:
                if constraint in self.columns:
                    node = Node(None, None)
                    column = self.columns[constraint]
                    column.pushUp(node)
                    row.pushLeft(node)

    def removeVariable(self, variable):
        if variable in self.rows:
            row = self.rows[variable]
            row.cloackRow()

    def removeClue(self, variable):
        if variable in self.rows:
            row = self.rows[variable]
            row.cloackRowComplex()


class Node():

    def __init__(self, constraint, variable):
        self.left = self
        self.right = self
        self.up = self
        self.down = self
        self.column = self
        self.row = self
        self.head = self
        self.size = 0
        self.constraint = constraint
        self.variable = variable

    def pushLeft(self, node):
        node.head = self.head
        node.row = self.row
        node.left = self.left
        node.right = self
        self.left.right = node
        self.left = node
        self.row.size += 1
        return self

    def pushUp(self, node):
        node.head = self.head
        node.column = self.column
        node.up = self.up
        node.down = self
        self.up.down = node
        self.up = node
        self.column.size += 1
        return self

    def cloackRow(self):
        for i in takewhile(
                lambda n: n != self.row,
                (n for n in self.row.nextRight())
        ):
            i.cloakFromColumn()
        self.row.cloakFromColumn()
        return self

    def cloackRowComplex(self):
        for i in takewhile(
                lambda n: n != self.row,
                (n for n in self.row.nextRight())
        ):
            i.column.cover()
        return self

    def cloakFromRow(self):
        if self.row == self:
            return self
        self.left.right = self.right
        self.right.left = self.left
        self.row.size -= 1
        return self

    def cloakFromColumn(self):
        if self.column == self:
            return self
        self.up.down = self.down
        self.down.up = self.up
        self.column.size -= 1
        return self

    def uncloakToRow(self):
        if self.row == self:
            return self
        self.left.right = self
        self.right.left = self
        self.row.size += 1
        return self

    def uncloakToColumn(self):
        if self.column == self:
            return self
        self.up.down = self
        self.down.up = self
        self.column.size += 1
        return self

    def cover(self):
        if self.column == self.head:
            return self
        self.column.cloakFromRow()
        for i in takewhile(
                lambda n: n != self.column,
                (n for n in self.column.nextDown())
        ):
            for j in takewhile(
                    lambda n: n != i, (n for n in i.nextRight())
            ):
                j.cloakFromColumn()
        return self

    def uncover(self):
        if self.column == self.head:
            return self
        for i in takewhile(
                lambda n: n != self.column,
                (n for n in self.column.nextUp())
        ):
            for j in takewhile(
                    lambda n: n != i, (n for n in i.nextLeft())
            ):
                j.uncloakToColumn()
        self.column.uncloakToRow()
        return self

    def nextLeft(self):
        node = self.left
        while True:
            yield node
            node = node.left

    def nextRight(self):
        node = self.right
        while True:
            yield node
            node = node.right

    def nextUp(self):
        node = self.up
        while True:
            yield node
            node = node.up

    def nextDown(self):
        node = self.down
        while True:
            yield node
            node = node.down
