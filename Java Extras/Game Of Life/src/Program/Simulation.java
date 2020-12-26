package Program;

public class Simulation {

    int width;
    int height;
    int[][] board;

    public Simulation(int width, int height) {
        this.width = width;
        this.height = height;
        board = new int[width][height];
    }

    public void setAlive(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return;
        board[x][y] = 1;
    }

    public void setDead(int x, int y) {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return;
        board[x][y] = 0;
    }

    public int countAliveNeighbours(int x, int y) {
        int count = 0;
        count += getCellValue(x - 1, y - 1);
        count += getCellValue(x, y - 1);
        count += getCellValue(x + 1, y - 1);

        count += getCellValue(x + 1, y);
        count += getCellValue(x - 1, y);

        count += getCellValue(x - 1, y + 1);
        count += getCellValue(x, y + 1);
        count += getCellValue(x + 1, y + 1);

        return count;
    }

    public int getCellValue(int x, int y) {
        if (x < 0 || x >= width)
            return 0;
        if (y < 0 || y >= height)
            return 0;
        return board[x][y];

    }

    public void step() {
        int[][] newBoard = new int[width][height];
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int aliveNeighbours = countAliveNeighbours(x, y);
                if (getCellValue(x, y) == 1) {
                    if (aliveNeighbours < 2) {
                        newBoard[x][y] = 0;
                    } else if (aliveNeighbours == 2 || aliveNeighbours == 3) {
                        newBoard[x][y] = 1;
                    } else {
                        newBoard[x][y] = 0;
                    }
                } else if (aliveNeighbours == 3) {
                    newBoard[x][y] = 1;
                }
            }
        }
        board = newBoard;
    }

    public void toggleState(int x, int y) {
        if (getCellValue(x, y) == 0) setAlive(x, y);
        else setDead(x, y);
    }
}
