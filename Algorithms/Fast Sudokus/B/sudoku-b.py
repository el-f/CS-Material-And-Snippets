from copy import deepcopy
import itertools as it
import numpy as np



class SudokuError(Exception):
    pass

class Sudoku(object):
    def __init__(self, board):
        self.board = board

    @classmethod
    def from_square(cls, board):
        for cell in it.chain(*board):
            if not isinstance(cell, int):
                raise SudokuError('Puzzle contain non digit charcters')
        
        cube =  [[set(range(1,10)) if cell == 0 else set([cell]) for cell in row] for row in board]
        return cls(cube)

    def rank(self):
        """ A completely solved board is of rank 0"""
        return sum(map(len, it.chain(*self.board))) - 9*9

    @property
    def is_solved(self):
        return self.rank() == 0

    def guess(self):

        min_cell, min_row, min_col = set(range(1, 10)), 0, 0
        for i, row in enumerate(self.board):
            for j, cell in enumerate(row):
                if len(min_cell) > len(cell) >= 2:
                    min_cell, min_row, min_col = cell, i, j


        for option in min_cell:
            new_board = deepcopy(self.board)
            new_board[min_row][min_col].clear()
            new_board[min_row][min_col].add(option)
            new_sudoku = Sudoku(new_board)
            yield new_sudoku



    def square(self):
        """ Return the sudoko as readable 2D list of integers: """
        return [[list(cell).pop() if len(cell) == 1 else 0 for cell in row] for row in self.board]

    def reduce_possibilities(self):
        """ Given a sudoko solution reduce the number of possiblities per cell"""
        while True:
            before = self.rank()
            # Rows:
            for row in self.board:
                self.reduce_row(row)

            # Coloumns:
            for row in zip(*self.board):
                self.reduce_row(row)

            # Boxes:
            boxes_to_rows = []
            for i, j in it.product([0, 1, 2], [0, 1, 2]):
                boxes_to_rows.append([cell for row in self.board[3*i: 3*i + 3] for cell in row[3*j: 3*j + 3]])

            for row in boxes_to_rows:
                self.reduce_row(row)

            # Break test
            after = self.rank()
            if before == after:
                break

    def reduce_row(self, row):
        """ Minimize number of options for each cell for every row """

        # len 1 sets are known, longer sets are unknown:
        known = [cell.copy().pop() for cell in row if len(cell) == 1]
        known_set = set(known)
        if len(known_set) != len(known):
            raise SudokuError("Repeating Value")
        unknown = [cell for cell in row if len(cell) > 1]
        uknown_set = set(range(1, 10)).difference(known_set)

        # All known options are remove from the unknown sets:
        for cell in unknown:
            cell.difference_update(known_set)
            if not cell:
                raise SudokuError("Cell without possibilities")

        # Some more immidate deductions for speedup:
        for k in [1, 2]:
            for nums in it.combinations(uknown_set, k):
                option_counter = 0
                aditional_options = False
                cell_ref = []
                for cell in unknown:
                    if set(nums).issubset(cell):
                        option_counter += 1
                        cell_ref.append(cell)
                    elif set(nums).intersection(cell):
                        aditional_options = True
                if option_counter == k and not aditional_options:
                    for cell in cell_ref:
                        cell.clear()
                        cell.update(nums)




def solve(sudoku):
    # breakout if sudoko is unsolvable:
    try:
        sudoku.reduce_possibilities()
    except SudokuError:
        return
    # or complete solution have been found:
    if sudoku.is_solved:
        return sudoku

    # Recurse over following options:
    solution = None
    for next_guess in sudoku.guess():
        result = solve(next_guess)
        if result:
            if solution:
                raise SudokuError("More than one solution")
            else:
                solution = result

    return solution


def sudoku_solver(puzzle):
    sudoku = Sudoku.from_square(puzzle)
    solution = solve(sudoku)
    if solution is None:
        raise SudokuError("No valid solution is possible")
    else:
        return solution.square()
