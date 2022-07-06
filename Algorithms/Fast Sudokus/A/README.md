# Fast Sudoku solver in Python with forward propagation

This is a fast Sudoku solver written in Python. It is inspired by the algorithm for solving constraint satisfaction problems (CSP). Essentially, it is a hard-coded CSP solver specifically for Sudoku.

The order of assignment of variables is determined by the minimum remaining values heuristic (MRV). This ensures that the search space is reduced very fast, and it fails quickly.

If a value is set, this value is removed from all the neighbouring cells that share the same constraint. If a cell has no more allowed values remaining, then the assignment is invalid (unless it is the last cell). 

This method gives two cool benefits:
    
1. The first is that if a puzzle can be solved without guessing, the algorithm will follow this route. This is the result of the MRV heuristic.

2. Secondly, we do not have to check if the contraints are met. Because the assigned value is removed from the allowed values for every cell that shares the same constraint, it is impossible to assign an invalid value, unless the puzzle is invalid to begin with.


## Example usage

```python
hardest_puzzle = "800000000003600000070090200050007000000045700000100030001000068008500010090000400"

from sudoku import SudokuSolver

solver = SudokuSolver(hardest_puzzle)
solver.solve()
solver.print_board()
solver.print_statistics()
```

Running the example will give the following output:

```
------- board -------
8 1 2 | 7 5 3 | 6 4 9
9 4 3 | 6 8 2 | 1 7 5
6 7 5 | 4 9 1 | 2 8 3
---------------------
1 5 4 | 2 3 7 | 8 9 6
3 6 9 | 8 4 5 | 7 2 1
2 8 7 | 1 6 9 | 5 3 4
---------------------
5 2 1 | 9 7 4 | 3 6 8
4 3 8 | 5 2 6 | 9 1 7
7 9 6 | 3 1 8 | 4 5 2

------- statistics -------
Total assignments: 14393
Runtime: 0.3474690914154053 seconds
```

If the provided puzzle string is an invalid puzzle, the solver will throw an `InvalidPuzzleError`.

It can also easily be modified to find all the possible solutions. Simply save the solutions in the `search(...)` function when the cell is `NO_CELLS_REMAINING`, and return `False`. Don't forget to reassign the board with a solution in the `solve(...)` method, otherwise the board is empty.

## Improvements

When forward propagating, we can speed it up even more:

 1. If the remaining values of a neighbour is only one value, we can remove this value from all of his neighbours. This should be done recursively too!
 2. If case 1 happens, fill in that value, and forward propagate that one too! Currently, the algorithm only forward propagates for one step... :c

Other ideas:

 1. Use an ordering for value selection. Perhaps used in most/least constraints, idk, test this!
 2. Encode the possible values as an integer with bit shifting, we can then just check an int, instead of iterating a list. First tests of this resulted in a much slower (x10 performance) implementation, so this idea should be explored in a better way. Also worthwhile to note: counting the possible values then results in the Hamming problem, which is also not that straightforward...
