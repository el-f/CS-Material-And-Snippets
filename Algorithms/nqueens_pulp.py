from pulp import *

def turn_mat_to_q_string(mat):
    return '\n'.join(''.join('Q' if bool(i.varValue) else '.' for i in arr) for arr in mat) + "\n"

def solve_n_queens(n, mandatory_position=None):
    """
    Solves the n-queens problem using pulp.
    Pulp is a python library for linear programming.
    
    Since the n-queens problem can be formulated as a linear programming problem,
    we can use pulp to solve it.

    Args:
        n (int): The size of the board.
        mandatory_position (tuple, optional): A tuple of the form (i, j) where i is the row and j is the column of the mandatory queen. Defaults to None.
        

    Returns:
        str: A string representing the board with the queens.
    """
    queens = LpProblem('queens')

    x = [[LpVariable(f'x({i},{j})', 0, 1, 'Binary') for j in range(n)] for i in range(n)]
    
    # no objective function - we only want to find a solution, there is no "best" solution

    # exactly one queen per row
    for i in range(n):
        queens += lpSum(x[i][j] for j in range(n)) == 1
    
    # exactly one queen per column
    for j in range(n):
        queens += lpSum(x[i][j] for i in range(n)) == 1

    # at most one queen per diagonal \
    for _, k in enumerate(range(-n + 1, n)):
        queens += lpSum(x[i][j] for i in range(n) for j in range(n) if i - j == k) <= 1

    # at most one queen per diagonal /
    for _, k in enumerate(range(0, 2 * n - 1)):
        queens += lpSum(x[i][j] for i in range(n) for j in range(n) if i + j == k) <= 1

    # if mandatory_position is given, add it to the constraints
    if mandatory_position:
        queens += x[mandatory_position[0]][mandatory_position[1]] == 1
        
    queens.solve()
    
    if LpStatus[queens.status] == 'Optimal':
        return turn_mat_to_q_string(x)

    return "No solution found."

print(solve_n_queens(8, (1, 1)))
