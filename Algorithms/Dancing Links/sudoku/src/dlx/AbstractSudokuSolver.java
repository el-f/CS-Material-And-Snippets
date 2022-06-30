package dlx;

import java.util.Arrays;

abstract class AbstractSudokuSolver {

    protected int S = 9; // size of the board
    protected int side = 3; // how long the side is

    // prints out all possible solutions. returns false if `sudoku` is invalid
    // to be implemented by concrete classes
    protected abstract void runSolver(int[][] sudoku);

    public boolean solve(int[][] sudoku) {
        if (!validateSudoku(sudoku)) {
            System.out.println("Error: Invalid sudoku. Aborting....");
            return false;
        }
        S = sudoku.length;
        side = (int) Math.sqrt(S);
        runSolver(sudoku);
        return true;
    }

    public boolean solve(String[] s) {
        return solve(fromCharArr(s));
    }


    private static int[][] fromCharArr(String[] s) {
        int S = s.length;
        int[][] out = new int[S][S];
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < S; j++) {
                int num = s[i].charAt(j) - '1';
                if (num >= 1 && num <= S)
                    out[i][j] = num;
            }
        }
        return out;
    }

    public static void printSolution(int[][] result) {
        int N = result.length;
        for (int i = 0; i < N; i++) {
            String ret = "";
            for (int j = 0; j < N; j++) {
                ret += result[i][j] + " ";
            }
            System.out.println(ret);
        }
        System.out.println();
    }


    // Checks whether `grid` represents a valid sudoku puzzle.
    // O's represent empty cells. 1..n^2 represent numbers in the grid.
    // Only allowed sizes are 9 and 16 for now. 
    protected static boolean validateSudoku(int[][] grid) {
        if (grid.length != 9 && grid.length != 16)
            return false; // only 9 or 16 for now
        for (int i = 0; i < grid.length; i++) {
            if (grid[i].length != grid.length)
                return false;
            for (int j = 0; j < grid[i].length; j++) {
                if (!(i >= 0 && i <= grid.length))
                    return false; // 0 means not filled in
            }
        }

        int N = grid.length;

        boolean[] b = new boolean[N + 1];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0)
                    continue;
                if (b[grid[i][j]])
                    return false;
                b[grid[i][j]] = true;
            }
            Arrays.fill(b, false);
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[j][i] == 0)
                    continue;
                if (b[grid[j][i]])
                    return false;
                b[grid[j][i]] = true;
            }
            Arrays.fill(b, false);
        }

        int side = (int) Math.sqrt(N);

        for (int i = 0; i < N; i += side) {
            for (int j = 0; j < N; j += side) {
                for (int d1 = 0; d1 < side; d1++) {
                    for (int d2 = 0; d2 < side; d2++) {
                        if (grid[i + d1][j + d2] == 0)
                            continue;
                        if (b[grid[i + d1][j + d2]])
                            return false;
                        b[grid[i + d1][j + d2]] = true;
                    }
                }
                Arrays.fill(b, false);
            }
        }
        return true;
    }


}
