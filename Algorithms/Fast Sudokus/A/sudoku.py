"""
Fast Sudoku solver with forward propagation of assigned values:

    The order of assignment of variables is determined by the minimum 
    remaining values heuristic (MRV). This ensures that the search space 
    is reduced very fast, and it fails quickly.

    If a value is set, this value is removed from all the neighbouring
    cells that share the same constraint. If a cell has no more allowed 
    values remaining, then the assignment is invalid (unless it is the 
    last cell). 

    This method gives two cool benefits:
        
        The first is that is that if a puzzle can be solved without 
        guessing, the algorithm will follow this route. This is the 
        result of the MRV heuristic.

        Secondly, we do not have to check if the contraints are met.
        Because the assigned value is removed from the allowed values
        for every cell that shares the same constraint, it is impossible
        to assign an invalid value, unless the puzzle is invalid to begin
        with.

Author: Lars Rotgers
Date:   5-3-2021
"""
from time import time

NO_REMAINING_CELLS = -1

class InvalidPuzzleError(Exception):
    pass

class SudokuSolver():
    """
    This Sudoku solver uses a customly designed CSP solving algorithm, 
    specifically for Sudoku. It requires a string of 81 characters, which
    represents the board.
    """

    def __init__(self, puzzle):
        """
        Initializes the board and the possible values for each cell.
        A "neighbours" look up table is also created. This is used to
        get all the neighbouring cells for a cell, that share the same
        constraints.

            board: the board is a list with 81 entries, one for
                   each cell.

            cells: contains 81 lists of possible values that can
                   be used for that cell.

            neighbours: contains 81 lists all the neighbours for
                        the indexed cell. Neighbours are defined as
                        the cells that share the same constraints.

        """
        self.runtime = 0
        self.total_assignments = 0
        self.board = [0] * 81
        self.allowed_values = [list(range(1, 10)) for _ in range(81)]
        self.assignments = 0
        self.initialize_neighbours()
        self.initialize_board(puzzle)

    def initialize_neighbours(self):
        """
        Initializes the neighbours list which holds the neighbours
        for each cell.
        """
        self.neighbours = []
        squares = [
            [ 0,  1,  2,  9, 10, 11, 18, 19, 20], 
            [ 3,  4,  5, 12, 13, 14, 21, 22, 23],
            [ 6,  7,  8, 15, 16, 17, 24, 25, 26],
            [27, 28, 29, 36, 37, 38, 45, 46, 47],
            [30, 31, 32, 39, 40, 41, 48, 49, 50],
            [33, 34, 35, 42, 43, 44, 51, 52, 53],
            [54, 55, 56, 63, 64, 65, 72, 73, 74],
            [57, 58, 59, 66, 67, 68, 75, 76, 77],
            [60, 61, 62, 69, 70, 71, 78, 79, 80]
        ]
        for cell in range(81):
            self.neighbours.append([])
            self.neighbours[cell] += list(range(9 * (cell // 9), 
                                                9 * (cell // 9) + 9))
            self.neighbours[cell] += list(range(cell % 9, 9 * 9, 9))
            for square in squares:
                if cell in square:
                    self.neighbours[cell] += square
                    break
            while cell in self.neighbours[cell]:
                self.neighbours[cell].remove(cell)

    def initialize_board(self, puzzle):
        """
        Assign the initial puzzle values to the board. 
        If an assignment of a value fails, then the puzzle
        is invalid, throws a InvalidPuzzleError.
        """
        for cell in range(81):
            if '1' <= puzzle[cell] <= '9':
                value = int(puzzle[cell])
                if not self.assign(cell, value, []):
                    raise InvalidPuzzleError()

    def assign(self, cell, value, removed_values):
        """
        Assign a value to a cell. It will return a list of tuples
        with all the removed values from all the cells. If it fails,
        the unassign(...) method must still be called to restore
        the removed values.
        """
        self.assignments += 1
        self.total_assignments += 1
        if value not in self.allowed_values[cell]:
            return False
        self.board[cell] = value
        for allowed_value in list(self.allowed_values[cell]):
            removed_values.append((cell, allowed_value))
            self.allowed_values[cell].remove(allowed_value)
        for neighbour in self.neighbours[cell]:
            if value in self.allowed_values[neighbour]:
                removed_values.append((neighbour, value))
                self.allowed_values[neighbour].remove(value)
                if self.assignments < 81 and not self.allowed_values[neighbour]:
                    return False
        return True

    def unassign(self, cell, removed_values):
        """
        Unassign a value from a cell. It also requires all the removed
        values from the assign(...) method, which is used to restore
        all the values that have been removed from the neighbours.
        """
        self.assignments -= 1
        self.board[cell] = 0
        for cell, removed_value in removed_values:
            self.allowed_values[cell].append(removed_value)

    def next_cell(self):
        """
        Returns the next cell that should be assigned. The next cell is
        the cell which has the minimum values remaining that can be assigned.
        The minimum value heuristic ensures the search space is reduced as
        quickly as possible, to fail early.
        """
        min_cell, min_values = (NO_REMAINING_CELLS, 10)
        for cell in range(81):
            if not self.board[cell]:
                num_values = len(self.allowed_values[cell])
                if num_values < min_values:
                    min_values = num_values
                    min_cell = cell
        return min_cell

    def search(self):
        """
        Goes through each cell, and assigns the possible values
        to solve the puzzle.
        """
        cell = self.next_cell()
        if cell == NO_REMAINING_CELLS:
            return True
        for value in self.allowed_values[cell]:
            removed_values = []
            success = self.assign(cell, value, removed_values)
            if success:
                if self.search():
                    return True
            self.unassign(cell, removed_values)
        return False

    def solve(self):
        """
        Solve the puzzle. If it raises an InvalidPuzzleError then
        the puzzle has no solution.
        """
        start = time()
        if not self.search():
            raise InvalidPuzzleError()
        end = time()
        self.runtime = end - start

    def print_board(self):
        """
        Prints the Sudoku board and all the available values available 
        that are available for each cell.
        """
        result = "------- board -------\r\n"
        for i in range(81):
            if i > 0 and i % 9 == 0:
                result += '\r\n'
            if i % 9 in (3, 6):
                result += '| '
            if i % 81 in (27, 54):
                result += '---------------------\r\n'
            result += str(self.board[i]) + ' '
        print(result)

    def print_available(self):
        result = '---------- available -----------\r\n'
        for i, values in enumerate(self.allowed_values):
            result += '{} | {}\r\n'.format(str(i + 1).rjust(2, ' '), values)
        print(result)

    def print_statistics(self):
        print('------- statistics -------')
        print('Total assignments: {}'.format(self.total_assignments))
        print('Runtime: {} seconds'.format(self.runtime))
